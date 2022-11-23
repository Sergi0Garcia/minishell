/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:59:51 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/10 11:47:12 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	n_len_ptr(uintptr_t n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static void	print_ptr(uintptr_t n)
{
	if (n >= 16)
	{
		print_ptr(n / 16);
		print_ptr(n % 16);
	}
	else
	{
		if (n < 10)
			ft_printf_char(n + '0');
		else
			ft_printf_char(n - 10 + 'a');
	}
}

int	ft_printf_ptr(unsigned long long ptr)
{
	int	len;

	ft_printf_char('0');
	ft_printf_char('x');
	len = 2;
	if (ptr == 0)
		len += ft_printf_char('0');
	else
	{
		print_ptr(ptr);
		len += n_len_ptr(ptr);
	}
	return (len);
}
