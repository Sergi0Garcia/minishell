/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:13:14 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/10 11:47:13 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	n_len_hex(unsigned int n)
{
	unsigned int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

int	ft_printf_hex(unsigned int n, char format)
{
	unsigned int	len;

	if (n == 0)
		return (ft_printf_char('0'));
	len = n_len_hex(n);
	if (n >= 16)
	{
		ft_printf_hex(n / 16, format);
		ft_printf_hex(n % 16, format);
	}
	else
	{
		if (n < 10)
			ft_printf_char(n + '0');
		else
		{
			if (format == 'x')
				ft_printf_char(n - 10 + 'a');
			if (format == 'X')
				ft_printf_char(n - 10 + 'A');
		}
	}
	return (len);
}
