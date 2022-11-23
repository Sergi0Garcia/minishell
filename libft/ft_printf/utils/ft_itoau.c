/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:21:53 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/09 14:20:37 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	n_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*handle_zero(char *str)
{
	str[0] = '0';
	str[1] = 0;
	return (str);
}

char	*ft_itoau(int n)
{
	size_t			i;
	char			*str;
	int				len;
	unsigned int	num;

	i = 0;
	num = n;
	len = n_len(n);
	if (n == 0)
		len = 1;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		return (handle_zero(str));
	while (num != 0)
	{
		str[len - i - 1] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	str[len] = 0;
	return (str);
}
