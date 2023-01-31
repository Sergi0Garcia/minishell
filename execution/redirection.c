/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:10:03 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/31 10:58:56 by rkanmado         ###   ########.fr       */
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
			return (-1);
		if (access(path, R_OK) == -1)
			return (-1);
		fd = open(path, O_RDONLY);
	}
	else if (key == DLESS)
	{
		fd = open(ft_strjoin("/tmp/heredocfile_", ft_itoa(i)), \
			O_CREAT | O_RDWR | O_TRUNC, 0777);
		hndle_here_doc(path, fd);
	}
	else if (key == GREAT)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (key == DGREAT)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
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
