/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:49:02 by segarcia          #+#    #+#             */
/*   Updated: 2022/05/23 13:53:47 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	size_t	rlen;
	char	*str;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	rlen = len;
	if (len > strlen)
		rlen = strlen;
	str = (char *)malloc(sizeof(char) * (rlen + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < strlen && s[start + i] && i < rlen)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
