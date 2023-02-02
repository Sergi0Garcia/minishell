/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:10:03 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/02 14:26:22 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_fd(char *path, t_wt key, int i)
{
	int	fd;

	fd = -1;
	if (!path)
		return (-1);
	if (key == LESS)
	{
		if (access(path, F_OK) == -1)
		{
			ci_error(ERR_PATH, 1);
			return (-1);
		}
		if (access(path, R_OK) == -1)
		{
			ci_error(ERR_PERMISSION, 1);
			return (-1);
		}
		fd = open(path, O_RDONLY);
	}
	else if (key == DLESS)
	{
		int		fda[2];
		
		if (pipe(fda) == -1)
		{
			ci_error(ERR_PIPE, 1);
			return (-1);
		}
		fd = open(ft_strjoin("/tmp/heredocfile_", ft_itoa(i)), \
			O_CREAT | O_RDWR | O_TRUNC, 0777);
		hndle_here_doc(path, fda[FD_WRITE_END]);
		close(fda[FD_WRITE_END]);
		return (fda[FD_READ_END]);
	}
	else if (key == GREAT)
	{
		if (access(path, F_OK) != -1 && access(path, W_OK) == -1)
		{
			ci_error(ERR_PERMISSION, 1);
			return (-1);
		}
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else if (key == DGREAT)
	{
		if (access(path, F_OK) != -1 && access(path, W_OK) == -1)
		{
			ci_error(ERR_PERMISSION, 1);
			return (-1);
		}
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	return (fd);
}

void	hndle_here_doc(char *eof, int fd)
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
