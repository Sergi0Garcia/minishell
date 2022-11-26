/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:14:47 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/26 18:14:38 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
	return ;
}

void	usage(void)
{
	error("Usage: ./mini_shell -c [command] \n Or \
			\n ./mini_shell -i \n Or ./mini_shell");
	return ;
}
