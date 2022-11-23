/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_intu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:06:23 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/09 14:27:53 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf_intu(unsigned int n)
{
	char	*num;
	int		len;

	len = 0;
	num = ft_itoau(n);
	len = ft_printf_str(num);
	free(num);
	return (len);
}
