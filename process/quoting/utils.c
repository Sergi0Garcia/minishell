/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 08:14:18 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/07 07:12:43 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strcat(char *s1, char *s2)
{
	int		counter;
	int		source_len;
	char	*result;
	int		result_len;

	result_len = (ft_strlen(s1) +ft_strlen(s2));
	result = s1;
	counter = 0;
	source_len = ft_strlen(s1);
	while (s2[counter] != '\0' && source_len + counter < result_len)
	{
		result[source_len + counter] = s2[counter];
		counter++;
	}
	result[source_len + counter] = '\0';
	return (result);
}

char	*ft_strcpy(char *dst, char *src)
{
	int		counter;

	counter = 0;
	while (src[counter] != '\0')
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
	return (dst);
}

char	*ft_strjoinsh(char *s1, char *s2)
{
	char	*result;
	int		len;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		*s1 = '\0';
	}
	if (s2 == NULL)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	result = malloc(len * sizeof(char));
	if (result == NULL)
		return (NULL);
	result = ft_strcpy(result, s1);
	result = ft_strcat(result, s2);
	free(s1);
	return (result);
}
