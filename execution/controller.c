/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/04 15:35:37 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static int	fd_redirection(t_c *cmds, int fd[2])
{
	t_ci	cmd;

	cmd = cmds->ci;
	if (cmd.infile != STDIN_FILENO)
	{
		if (dup2(cmd.infile, STDIN_FILENO) == -1)
			return (ci_error(ERR_DUP2, 1));
		close(cmd.infile);
	}
	if (cmd.outfile != STDOUT_FILENO)
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

static int	execute_builtin(t_c *cmds, t_env **env_lst)
{
	t_ci	cmd;

	cmd = cmds->ci;
	if (is_same_str(cmd.name, "exit"))
		exit(EXIT_SUCCESS);
	else if (is_same_str(cmd.name, "echo"))
		g_status = ft_echo(cmd);
	else if (is_same_str(cmd.name, "cd"))
		g_status = ft_cd(cmds, env_lst);
	else if (is_same_str(cmd.name, "pwd"))
		ft_pwd(cmds, 1);
	else if (is_same_str(cmd.name, "export"))
		g_status = ft_export(cmd, env_lst);
	else if (is_same_str(cmd.name, "unset"))
		g_status = ft_unset(cmd, env_lst);
	else if (is_same_str(cmd.name, "env"))
		g_status = ft_env(cmd, env_lst);
	else if (is_file(cmd.name)
		&& file_validation(cmd.name))
		g_status = ft_execve(cmd, env_lst, 1);
	else
		g_status = ft_execve(cmd, env_lst, 0);
	return (g_status);
}

void	exec_fork(t_c *cmd, t_env **env_lst, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[FD_READ_END]);
		close(fd[FD_WRITE_END]);
		ci_error(ERR_FORK, 1);
		return ;
	}
	else if (!pid)
	{
		close(fd[FD_READ_END]);
		fd_redirection(cmd, fd);
		execute_builtin(cmd, env_lst);
		exit (g_status);
	}
}

void	execute_cmd(t_c *cmds, t_env **env_lst)
{
	int		fd[2];
	t_ci	cmd;

	cmd = cmds->ci;
	if (pipe(fd) == -1)
		ci_error(ERR_PIPE, 1);
	if (!valid_fork(cmds, env_lst))
		return ;
	exec_fork(cmds, env_lst, fd);
	close(fd[FD_WRITE_END]);
	if (cmds->next && !cmds->next->ci.infile)
		cmds->next->ci.infile = fd[FD_READ_END];
	else
		close (fd[FD_READ_END]);
	if (cmd.infile > 2)
		close (cmd.infile);
	if (cmd.outfile > 2)
		close (cmd.outfile);
	return ;
}

int	controller(t_minish *sh)
{
	t_c			*cmds;
	t_env		**env_lst;
	int			i;

	i = 0;
	cmds = sh->cmds.head;
	env_lst = &sh->env_lst;
	if (is_single_execution(cmds))
		return (execute_builtin(cmds, env_lst));
	while (cmds)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		execute_cmd(cmds, env_lst);
		cmds = cmds->next;
	}
	while (i++ <= sh->cmds.size)
		waitpid(-1, &g_status, 0);
	if (g_status > 255)
		g_status = g_status / 255;
	return (g_status);
}
