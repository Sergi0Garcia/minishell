/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/25 11:08:37 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

static int	fd_redirection(t_c *cmd, int fd[2])
{
	if (cmd->infile && cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
            return(EXIT_FAILURE);
		close(cmd->infile);
	}
	if (cmd->outfile && cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
            return(EXIT_FAILURE);
		close(cmd->outfile);
	}
	else if (cmd->next && dup2(fd[FD_WRITE_END], STDOUT_FILENO) == -1)
       return(EXIT_FAILURE);
	close(fd[FD_WRITE_END]);
	return (EXIT_SUCCESS);
}

static int	exec_builtin(t_c *cmd, t_env_node *env_lst)
{
    if (is_same_str(cmd->name, "echo"))
		ft_echo(cmd);
	else if (is_same_str(cmd->name, "cd"))
        ft_cd(cmd, &env_lst);
	else if (is_same_str(cmd->name, "pwd"))
        ft_pwd(cmd);
	else if (is_same_str(cmd->name, "export"))
		ft_export(cmd, &env_lst);
	else if (is_same_str(cmd->name, "unset"))
		ft_unset(cmd, &env_lst);
	else if (is_same_str(cmd->name, "env"))
		ft_env(cmd, &env_lst);
	else 
		ft_execve(&env_lst, cmd);
	return (EXIT_SUCCESS);
}

static int	child_process(t_c *cmd, t_env_node *env_lst, int fd[2])
{
	if (fd_redirection(cmd, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd[FD_READ_END]);
	exec_builtin(cmd, env_lst);
	exit(EXIT_SUCCESS);
}

int exec_fork(t_c *cmd, t_env_node *env_lst, int fd[2])
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
	return (EXIT_SUCCESS);
}

int	exec_cmd(t_c *cmd, t_env_node *env_lst)
{
	int		fd[2];

	if (pipe(fd) == -1)
        return (EXIT_FAILURE);
	// Missing validation to fork
	if (exec_fork(cmd, env_lst, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd[FD_WRITE_END]);
	if (cmd->next && !cmd->next->infile)
		cmd->next->infile = fd[FD_READ_END];
	else
		close(fd[FD_READ_END]);
	if (cmd && cmd->infile > 2)
		close(cmd->infile);
	if (cmd && cmd->outfile > 2)
		close(cmd->outfile);
	return (EXIT_SUCCESS);
}

int controller(t_c *cmd, t_env_node *env_lst)
{
    while (cmd)
    {
        if (exec_cmd(cmd, env_lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
        cmd = cmd->next;
    }
    return (EXIT_SUCCESS);
}
