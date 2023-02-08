/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_home_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:13:09 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/07 13:22:14 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	define_home_path(char **args)
{
	if (args[0][0] && args[0][0] == '~'
			&& ft_strlen(args[0]) == 1)
		return (1);
	if ((args[0][0] && args[0][1]
			&& args[0][0] == '~' && args[0][1] == '/'))
		return (2);
	return (3);
}

char	*free_return_args(char **args, char *res)
{
	return_free(args, 0);
	return (res);
}
