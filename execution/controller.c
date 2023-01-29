/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/29 09:19:28 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

static int is_single_cmd(t_c *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	if (i == 1)
		return (1);
	else
		return (0);
}

static int	is_single_execution(t_c *cmd)
{
	if (is_single_cmd(cmd)
		&& (is_same_str(cmd->ci.name, "exit")
		|| is_same_str(cmd->ci.name, "export")
		|| is_same_str(cmd->ci.name, "un`set")
		|| is_same_str(cmd->ci.name, "cd")))
			return (1);
	return (0);
}

static int	fd_redirection(t_c *cmd, int fd[2])
{
	if (cmd->ci.infile && cmd->ci.infile != STDIN_FILENO)
	{
		if (dup2(cmd->ci.infile, STDIN_FILENO) == -1)
            return(EXIT_FAILURE);
		close(cmd->ci.infile);
	}
	if (cmd->ci.outfile && cmd->ci.outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->ci.outfile, STDOUT_FILENO) == -1)
            return(EXIT_FAILURE);
		close(cmd->ci.outfile);
	}
	else if (cmd->next && dup2(fd[FD_WRITE_END], STDOUT_FILENO) == -1)
       return(EXIT_FAILURE);
	close(fd[FD_WRITE_END]);
	return (EXIT_SUCCESS);
}

static int is_executable_path(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

static int	exec_builtin(t_c *cmd, t_env_node **env_lst)
{
	if (is_same_str(cmd->ci.name, "exit"))
		exit(EXIT_SUCCESS);
    else if (is_same_str(cmd->ci.name, "echo"))
		ft_echo(cmd);
	else if (is_same_str(cmd->ci.name, "cd"))
        ft_cd(cmd, env_lst);
	else if (is_same_str(cmd->ci.name, "pwd"))
        ft_pwd(cmd);
	else if (is_same_str(cmd->ci.name, "export"))
		ft_export(cmd, env_lst);
	else if (is_same_str(cmd->ci.name, "unset"))
		ft_unset(cmd, env_lst);
	else if (is_same_str(cmd->ci.name, "env"))
		ft_env(cmd, env_lst);
	else if (is_executable_path(cmd->ci.name))
		ft_path_execve(cmd, env_lst);
	else
		ft_execve(cmd, env_lst);
	return (EXIT_SUCCESS);
}

static int	child_process(t_c *cmd, t_env_node **env_lst, int fd[2])
{
	if (fd_redirection(cmd, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd[FD_READ_END]);
	exec_builtin(cmd, env_lst);
	exit(EXIT_SUCCESS);
}

int exec_fork(t_c *cmd, t_env_node **env_lst, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[FD_READ_END]);
		close(fd[FD_WRITE_END]);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (child_process(cmd, env_lst, fd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);
	return (EXIT_SUCCESS);
}

int	exec_cmd(t_c *cmd, t_env_node **env_lst)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		close(fd[FD_WRITE_END]);
        return (EXIT_FAILURE);
	}
	if (cmd->ci.infile == -1 || cmd->ci.outfile == -1)
	{
		close(fd[FD_WRITE_END]);
		return (EXIT_FAILURE);
	}
	if (exec_fork(cmd, env_lst, fd) == EXIT_FAILURE)
	{
		close(fd[FD_WRITE_END]);
		return (EXIT_FAILURE);
	}
	close(fd[FD_WRITE_END]);
	if (cmd->next && !cmd->next->ci.infile)
		cmd->next->ci.infile = fd[FD_READ_END];
	else
		close(fd[FD_READ_END]);
	if (cmd && cmd->ci.infile > 2)
		close(cmd->ci.infile);
	if (cmd && cmd->ci.outfile > 2)
		close(cmd->ci.outfile);
	return (EXIT_SUCCESS);
}

int	controller(t_minish *sh)
{
	t_c			*cmd;
	t_env_node	**env_lst;

	cmd = sh->cmds.head;
	env_lst = &sh->env_lst;
	if (is_single_execution(cmd))
		return (exec_builtin(cmd, env_lst));
	while (cmd)
	{
		exec_cmd(cmd, env_lst);
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
