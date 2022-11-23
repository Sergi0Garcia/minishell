/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:48:48 by segarcia          #+#    #+#             */
/*   Updated: 2022/05/20 12:38:31 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*substr;

	start = 0;
	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	start = i;
	i = ft_strlen(s1);
	while (i > start && is_in_set(s1[i - 1], set))
		i--;
	end = i;
	substr = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s1 + start, end - start + 1);
	return (substr);
}
