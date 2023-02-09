/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:10:03 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/09 04:47:46 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_fd(char *path, t_wt key, int *i)
{
	int	fd[2];

	if (!path)
		return (-1);
	if (key == LESS)
		return (fd_less(path));
	else if (key == GREAT)
		return (fd_great(path));
	else if (key == DGREAT)
		return (fd_dgreat(path));
	else if (key == DLESS)
	{
		if (pipe(fd) == -1)
		{
			ci_error(ERR_PIPE, 1);
			return (-1);
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (handle_here_doc(path, fd[FD_WRITE_END]) == false)
			*i = -1;
		close(fd[FD_WRITE_END]);
		return (fd[FD_READ_END]);
	}
	return (-1);
}

t_b	handle_here_doc(char *eof, int fd)
{
	char	*line[2];

	line[0] = readline("> ");
	line[1] = NULL;
	while (1)
	{
		if (!line[0])
			return (false);
		if (is_same_str(line[0], eof))
			break ;
		line[1] = readline("> ");
		ft_putendl_fd(line[0], fd);
		free(line[0]);
		line[0] = line[1];
	}
	if (line[1] != NULL)
		free(line[1]);
	return (true);
}
