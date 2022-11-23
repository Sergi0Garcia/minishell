/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:14:54 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/09 14:34:17 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_printf.h"

static int	ft_print_handler(va_list args, const char format)
{
	int	print_len;

	print_len = 0;
	if (format == 'c')
		print_len += ft_printf_char(va_arg(args, int));
	if (format == 's')
		print_len += ft_printf_str(va_arg(args, char *));
	if (format == 'p')
		print_len += ft_printf_ptr(va_arg(args, unsigned long long));
	if (format == 'd' || format == 'i')
		print_len += ft_printf_int(va_arg(args, int));
	if (format == 'u')
		print_len += ft_printf_intu(va_arg(args, unsigned int));
	if (format == 'x' || format == 'X')
		print_len += ft_printf_hex(va_arg(args, unsigned int), format);
	if (format == '%')
		print_len += ft_printf_char('%');
	return (print_len);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	int			print_len;
	va_list		arg;

	i = 0;
	print_len = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_len += ft_print_handler(arg, str[i + 1]);
			i++;
		}
		else
			print_len += ft_printf_char(str[i]);
		i++;
	}
	va_end(arg);
	return (print_len);
}
