/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:53 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/04 12:13:21 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_usage(int argc, char **argv, t_minish *sh)
{
	if (argc < 1 || argc > 3)
		usage();
	if (argc == 1)
		sh->interactive = true;
	else if ((ft_strcmp(argv[1], "-i") == 0 && argc == 2))
		sh->interactive = true;
	else if (ft_strcmp(argv[1], "-c") != 0 && (argc == 2 || argc == 3))
		usage();
	return ;
}

void	usage(void)
{
	error("Usage: ./mini_shell -c [command] \n Or \
			\n ./mini_shell -i \n Or ./mini_shell");
	return ;
}

t_b	can_add_opt(char *args)
{
	if (ft_strlen(args) > 0)
		return (false);
	return (true);
}
