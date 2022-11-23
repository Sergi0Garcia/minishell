/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:00:58 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/09 14:50:05 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf_str(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_printf_char('(');
		ft_printf_char('n');
		ft_printf_char('u');
		ft_printf_char('l');
		ft_printf_char('l');
		ft_printf_char(')');
		return (6);
	}
	while (str[i])
	{
		ft_printf_char(str[i]);
		i++;
	}
	return (i);
}
