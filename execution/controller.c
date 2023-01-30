/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/30 03:49:02 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

extern int	g_status;

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

static int	fd_redirection(t_c *cmds, int fd[2])
{
	t_ci	cmd;

	cmd = cmds->ci;
	if (cmd.infile && cmd.infile != STDIN_FILENO)
	{
		if (dup2(cmd.infile, STDIN_FILENO) == -1)
            return (ci_error(ERR_DUP2, 1));
		close(cmd.infile);
	}
	if (cmd.outfile && cmd.outfile != STDOUT_FILENO)
	{
		if (dup2(cmd.outfile, STDOUT_FILENO) == -1)
            return (ci_error(ERR_DUP2, 1));
		close(cmd.outfile);
	}
	else if (cmds->next)
	{
		if (dup2(fd[FD_WRITE_END], STDOUT_FILENO) == -1)
	 		return (ci_error(ERR_DUP2, 1));
	}
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
	if (is_same_str(cmd->ci.name, "exit"))
		exit(EXIT_SUCCESS);
    else if (is_same_str(cmd->ci.name, "echo"))
		g_status = ft_echo(cmd->ci);
	else if (is_same_str(cmd->ci.name, "cd"))
        ft_cd(cmd, env_lst);
	else if (is_same_str(cmd->ci.name, "pwd"))
        ft_pwd(cmd, 1);
	else if (is_same_str(cmd->ci.name, "export"))
		ft_export(cmd->ci, env_lst);
	else if (is_same_str(cmd->ci.name, "unset"))
		ft_unset(cmd->ci, env_lst);
	else if (is_same_str(cmd->ci.name, "env"))
		g_status = ft_env(cmd->ci, env_lst);
	else if (is_executable_path(cmd->ci.name))
		g_status = ft_execve(cmd->ci, env_lst, 1);
	else
		g_status = ft_execve(cmd->ci, env_lst, 0);
	return (g_status);
}

static int	child_process(t_c *cmd, t_env **env_lst, int fd[2])
{
	if (fd_redirection(cmd, fd) == EXIT_FAILURE)
		return (1);
	close(fd[FD_READ_END]);
	exec_builtin(cmd, env_lst);
	exit (EXIT_SUCCESS);
}

int	 exec_fork(t_c *cmd, t_env **env_lst, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[FD_READ_END]);
		close(fd[FD_WRITE_END]);
		ci_error(ERR_FORK, 1);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process(cmd, env_lst, fd);
	printf("after child\n");
	return (EXIT_SUCCESS);
}

void	exec_cmds(t_c *cmds, t_env **env_lst)
{
	int		fd[2];
	t_ci	cmd;

	cmd = cmds->ci;
	if (pipe(fd) == -1)
		ci_error(ERR_PIPE, 1);
	if (cmd.infile == -1 || cmd.outfile == -1)
	{
		close(fd[FD_WRITE_END]);
		ci_error(ERR_NONE, 1);
	}
	if (exec_fork(cmds, env_lst, fd) == EXIT_FAILURE)
	{
		close(fd[FD_WRITE_END]);
		return ;
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
	return ;
}

int	controller(t_minish *sh)
{
	t_c			*cmds;
	t_env		**env_lst;

	cmds = sh->cmds.head;
	env_lst = &sh->env_lst;
	if (is_single_execution(cmds))
	{
		g_status = exec_builtin(cmds, env_lst);
		return (g_status);
	}
	while (cmds)
	{
		exec_cmds(cmds, env_lst);
		cmds = cmds->next;
	}
	return (g_status);
}
