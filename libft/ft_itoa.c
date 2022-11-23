/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:38:56 by segarcia          #+#    #+#             */
/*   Updated: 2022/05/10 13:29:03 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static void	validate_sign(int n, unsigned int *num, int *is_neg, int *len)
{
	*is_neg = 0;
	*len = 0;
	*num = n;
	if (n < 0)
	{
		*num = n * -1;
		*is_neg = 1;
	}
	*len = n_len(*num);
	if (n == 0)
		*len = 1;
}

static char	*handle_zero(char *str)
{
	str[0] = '0';
	str[1] = 0;
	return (str);
}

char	*ft_itoa(int n)
{
	size_t			i;
	char			*str;
	int				len;
	int				is_neg;
	unsigned int	num;

	i = 0;
	validate_sign(n, &num, &is_neg, &len);
	str = (char *)malloc(len + is_neg + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		return (handle_zero(str));
	if (is_neg)
		str[0] = '-';
	while (num != 0)
	{
		str[len - i - !is_neg] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	str[len + is_neg] = 0;
	return (str);
}
