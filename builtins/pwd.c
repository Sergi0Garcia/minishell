/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:21:50 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/24 09:32:50 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX))
	{
		printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
