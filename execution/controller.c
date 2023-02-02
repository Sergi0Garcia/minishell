/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/02 01:09:33 by segarcia         ###   ########.fr       */
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
	else if (cmds->next && dup2(fd[FD_WRITE_END], STDOUT_FILENO) == -1)
	 	return (ci_error(ERR_DUP2, 1));
	close(fd[FD_WRITE_END]);
	return (EXIT_SUCCESS);
}

static int	is_executable_path(char *path)
{
	if (access(path, X_OK) == -1)
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
       	g_status = ft_cd(cmd, env_lst);
	else if (is_same_str(cmd->ci.name, "pwd"))
        ft_pwd(cmd, 1);
	else if (is_same_str(cmd->ci.name, "export"))
		g_status = ft_export(cmd->ci, env_lst);
	else if (is_same_str(cmd->ci.name, "unset"))
		g_status = ft_unset(cmd->ci, env_lst);
	else if (is_same_str(cmd->ci.name, "env"))
		g_status = ft_env(cmd->ci, env_lst);
	else if (is_executable_path(cmd->ci.name))
		g_status = ft_execve(cmd->ci, env_lst, 1);
	else
		g_status = ft_execve(cmd->ci, env_lst, 0);
	return (g_status);
}

void	*child_process(t_c *cmd, t_env **env_lst, int fd[2])
{
	close(fd[FD_READ_END]);
	fd_redirection(cmd, fd);
	exec_builtin(cmd, env_lst);
	exit (g_status);
}

void	 exec_fork(t_c *cmd, t_env **env_lst, int fd[2])
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
		child_process(cmd, env_lst, fd);
}

static char *check_to_fork(t_c *cmds, t_env **env_lst, int fd[2])
{
	char	*cmd_path;
	int		is_executable;

	cmd_path = get_cmd_path(env_lst, cmds->ci.name);
	is_executable = is_executable_path(cmds->ci.name);
	if (cmds->ci.infile == -1 || cmds->ci.outfile == -1)
	    return ("");
	if (!cmd_path && !is_executable)
	{
		ci_error(ERR_CMD_FOUND, 127);
		g_status = 127;
		return ("");
	}
	exec_fork(cmds, env_lst, fd);
	return ("");
}

void	exec_cmds(t_c *cmds, t_env **env_lst)
{
	int		fd[2];
	t_ci	cmd;

	cmd = cmds->ci;

	if (pipe(fd) == -1)
		ci_error(ERR_PIPE, 1);
	if (!check_to_fork(cmds, env_lst, fd))
	{
		return ;
	}
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
		return (exec_builtin(cmds, env_lst));
	while (cmds)
	{
		exec_cmds(cmds, env_lst);
		cmds = cmds->next;
	}
	while (i++ <= sh->cmds.size)
		waitpid(-1, &g_status, 0);
	if (g_status > 255)
		g_status = g_status / 255;
	return (g_status);
}
