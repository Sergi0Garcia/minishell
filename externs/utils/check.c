/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:53 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/26 18:52:02 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_usage(int argc, char **argv, t_minish *sh)
{
	if (argc < 1 || argc > 3)
		usage();
	if ((ft_strncmp(argv[1], "-i", ft_strlen("-i")) == 0 && argc == 2) \
		&& argc == 1)
		sh->interactive = 1;
	else if (ft_strncmp(argv[1], "-c", ft_strlen("-i")) == 0 && argc == 2)
		usage();
	return ;
}
