/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:10:03 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/03 04:02:17 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_fd(char *path, t_wt key, int i)
{
	int	fd[2];

	if (!path)
		return (-1);
	if (key == LESS)
		return (fd_less(path));
	else if (key == GREAT)
		return (fd_great(path));
	else if (key == DGREAT)
		fd_dgreat(path);
	else if (key == DLESS)
	{
		if (pipe(fd) == -1)
		{
			ci_error(ERR_PIPE, 1);
			return (-1);
		}
		fd = open(ft_strjoin("/tmp/heredocfile_", ft_itoa(i)), \
			O_CREAT | O_RDWR | O_TRUNC, 0777);
		handle_here_doc(path, fd[FD_WRITE_END]);
		close(fd[FD_WRITE_END]);
		return (fd[FD_READ_END]);
	}
	return (fd);
}

void	handle_here_doc(char *eof, int fd)
{
	char	*str;
	char	*line[2];

	str = ft_strdup("");
	line[0] = readline("> ");
	while (1)
	{
		if (!line[0])
			return ;
		signal(SIGINT, SIG_DFL);
		if (is_same_str(line[0], eof))
			break ;
		line[1] = readline("> ");
		str = ft_strjoin(str, line[1]);
		ft_putendl_fd(line[0], fd);
		free(line[0]);
		line[0] = line[1];
	}
	free(str);
	return ;
}
