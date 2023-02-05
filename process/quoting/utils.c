/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 08:14:18 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/05 12:32:11 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*ft_strcat(char *s1, const char *s2)
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

static char	*ft_strcpy(char *dst, const char *src)
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
