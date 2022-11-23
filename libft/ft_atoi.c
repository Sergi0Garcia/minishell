/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:30:09 by segarcia          #+#    #+#             */
/*   Updated: 2022/10/11 11:55:40 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	overflow(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

static void	sign_validation(char num, size_t *i, int *sign)
{
	*sign = 1;
	if (num == '-' || num == '+')
	{
		if (num == '-')
			*sign = -1;
		*i = *i + 1;
	}
}

int	ft_atoi(const char *str)
{
	unsigned long int		res;
	unsigned long int		gap;
	int						sign;
	size_t					i;

	i = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	sign_validation(str[i], &i, &sign);
	while (ft_isdigit(str[i]))
	{
		if ((((res * 10) + (str[i] - '0')) > LONG_MAX) && sign == 1)
			return (overflow(sign));
		if ((((res * 10) + (str[i] - '0')) > LONG_MAX) && sign == -1)
			return (overflow(sign));
		gap = ULLONG_MAX - (((res * 10) + (str[i] - '0')) * 10);
		if (str[i + 1] && ft_isdigit(str[i + 1])
			&& gap < (unsigned long)(str[i + 1] - '0'))
			return (overflow(sign));
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return ((int)res * sign);
}
