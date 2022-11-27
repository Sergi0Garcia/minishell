/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:04:51 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 01:30:31 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(char *str)
{
	int res;

	// We need to handle following cases
	// cd - (Search for $LASTPWD)
	// cd ~ (append $HOME)

	res = chdir(str);
	if (res == -1)
		 perror("Error: ");
	printf("%i\n", res);
}