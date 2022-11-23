/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:54:35 by segarcia          #+#    #+#             */
/*   Updated: 2022/07/12 12:06:25 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	get_nl_idx(char *ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		if (ptr[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}

void	cpystr_increment(char *s1, char *s2, size_t *num)
{
	if (!s1 || !s2)
		return ;
	s1[*num] = s2[*num];
	*num = *num + 1;
}

static char	*ft_strdup(char *src)
{
	size_t	len;
	size_t	i;
	char	*dest;

	len = ft_strlen(src);
	dest = malloc(len + 1);
	i = 0;
	if (dest == 0)
		return (0);
	else
	{
		while (src[i])
			cpystr_increment(dest, src, &i);
		dest[i] = '\0';
		return (dest);
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len1)
		cpystr_increment(str, s1, &i);
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}
