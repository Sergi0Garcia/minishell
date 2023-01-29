/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/29 20:04:04 by segarcia         ###   ########.fr       */
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
		|| is_same_str(cmd->ci.name, "unset")
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

static int	exec_builtin(t_c *cmd, t_env **env_lst)
{
	(void) env_lst;
	if (is_same_str(cmd->ci.name, "exit"))
		exit(EXIT_SUCCESS);
    else if (is_same_str(cmd->ci.name, "echo"))
		ft_echo(cmd->ci);
	else if (is_same_str(cmd->ci.name, "cd"))
        ft_cd(cmd, env_lst);
	else if (is_same_str(cmd->ci.name, "pwd"))
        ft_pwd(cmd, 1);
	else if (is_same_str(cmd->ci.name, "export"))
		ft_export(cmd->ci, env_lst);
	else if (is_same_str(cmd->ci.name, "unset"))
		ft_unset(cmd->ci, env_lst);
	else if (is_same_str(cmd->ci.name, "env"))
		ft_env(cmd->ci, env_lst);
	else if (is_executable_path(cmd->ci.name))
		ft_execve(cmd->ci, env_lst, 1);
	else
		ft_execve(cmd->ci, env_lst, 0);
	return (EXIT_SUCCESS);
}

static int	child_process(t_c *cmd, t_env **env_lst, int fd[2])
{
	if (fd_redirection(cmd, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd[FD_READ_END]);
	exec_builtin(cmd, env_lst);
	exit(EXIT_SUCCESS);
}

int exec_fork(t_c *cmd, t_env **env_lst, int fd[2])
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
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	exec_cmds(t_c *cmds, t_env **env_lst)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		close(fd[FD_WRITE_END]);
        return (EXIT_FAILURE);
	}
	if (cmds->ci.infile == -1 || cmds->ci.outfile == -1)
	{
		close(fd[FD_WRITE_END]);
		return (EXIT_FAILURE);
	}
	if (exec_fork(cmds, env_lst, fd) == EXIT_FAILURE)
	{
		close(fd[FD_WRITE_END]);
		return (EXIT_FAILURE);
	}
	close(fd[FD_WRITE_END]);
	if (cmds->next && !cmds->next->ci.infile)
		cmds->next->ci.infile = fd[FD_READ_END];
	else
		close(fd[FD_READ_END]);
	if (cmds && cmds->ci.infile > 2)
		close(cmds->ci.infile);
	if (cmds && cmds->ci.outfile > 2)
		close(cmds->ci.outfile);
	return (EXIT_SUCCESS);
}

int	controller(t_minish *sh)
{
	t_c			*cmds;
	t_env		**env_lst;

	cmds = sh->cmds.head;
	env_lst = &sh->env_lst;

	printf("cmd.name =%s\n", cmds->ci.name);
	printf("cmd.opts =%s\n", cmds->ci.opts);
	printf("cmd.args =%s\n", cmds->ci.args);
	
	if (is_single_execution(cmds))
		return (exec_builtin(cmds, env_lst));;
	while (cmds)
	{
		exec_cmds(cmds, env_lst);
		cmds = cmds->next;
	}
	return (EXIT_SUCCESS);
}
