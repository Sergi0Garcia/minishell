/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/05 02:55:17 by rkanmado         ###   ########.fr       */
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

static int	execute_builtin(t_c *cmds, t_env **env_lst, int single, t_minish *sh)
{
	t_ci	cmd;

	cmd = cmds->ci;
	if (is_same_str(cmd.name, "exit") && single)
	{
		exit (ft_exit(cmd, sh));
	}
	if (is_same_str(cmd.name, "exit") && !single)
		return (g_status);
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

void	sig_quit_from_child(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	(void) info;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_int(void)
{
	struct sigaction	sa_res;

	sa_res.sa_flags = SA_SIGINFO;
	sa_res.sa_sigaction = &sig_quit_from_child;
	sigaction(SIGINT, &sa_res, NULL);
	return ;
}

void	exec_fork(t_c *cmd, t_env **env_lst, int fd[2], t_minish *sh)
{
	pid_t	pid;

	signal(SIGQUIT, SIG_IGN);
	sig_int();
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
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		close(fd[FD_READ_END]);
		fd_redirection(cmd, fd);
		execute_builtin(cmd, env_lst, 0, sh);
		exit (g_status);
	}
}

void	execute_cmd(t_c *cmds, t_env **env_lst, t_minish *sh)
{
	int		fd[2];
	t_ci	cmd;

	cmd = cmds->ci;
	if (pipe(fd) == -1)
		ci_error(ERR_PIPE, 1);
	if (!valid_fork(cmds, env_lst))
		return ;
	exec_fork(cmds, env_lst, fd, sh);
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
		return (execute_builtin(cmds, env_lst, 1, sh));
	while (cmds)
	{
		execute_cmd(cmds, env_lst, sh);
		cmds = cmds->next;
	}
	while (i++ <= sh->cmds.size)
		waitpid(-1, &g_status, 0);
	if (g_status > 255)
		g_status = g_status / 255;
	return (g_status);
}
