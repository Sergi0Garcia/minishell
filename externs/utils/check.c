/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:53 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/27 06:07:54 by rkanmado         ###   ########.fr       */
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
	else if (ft_strcmp(argv[1], "-c") == 0 && (argc == 2 || argc == 3))
		usage();
	return ;
}
