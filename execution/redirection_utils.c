/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 03:49:19 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/03 04:32:35 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fd_less(char *path)
{
	int	fd;

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
	return (fd);
}

int	fd_great(char *path)
{
	int	fd;

	if (access(path, F_OK) != -1 && access(path, W_OK) == -1)
	{
		ci_error(ERR_PERMISSION, 1);
		return (-1);
	}
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return (fd);
}

int	fd_dgreat(char *path)
{
	int	fd;

	if (access(path, F_OK) != -1 && access(path, W_OK) == -1)
	{
		ci_error(ERR_PERMISSION, 1);
		return (-1);
	}
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	return (fd);
}
