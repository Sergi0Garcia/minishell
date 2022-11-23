/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:44:16 by segarcia          #+#    #+#             */
/*   Updated: 2022/04/20 12:44:18 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_length;
	size_t	src_length;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen((char *)(src));
	i = 0;
	if (dstsize > 0 && dst_length < dstsize - 1)
	{
		while (src[i] && (dst_length + i) < dstsize - 1)
		{
			dst[i + dst_length] = src[i];
			i++;
		}
		dst[i + dst_length] = '\0';
	}
	if (dst_length >= dstsize)
		dst_length = dstsize;
	return (dst_length + src_length);
}
