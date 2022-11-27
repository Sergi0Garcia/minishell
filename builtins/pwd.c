/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:21:50 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 01:11:44 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pwd(char *buffer, int buff_size)
{
	char	*ptr;

	ptr = NULL;
	ptr = getcwd(buffer, buff_size);
	// if error; path = NULL;
	return (ptr);
}
