/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:47:52 by segarcia          #+#    #+#             */
/*   Updated: 2022/05/21 19:06:46 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	flag_ckpt(const char *str, char c, int *ckpt)
{
	int	flag;

	flag = 0;
	if (*str != c && *ckpt == 0)
	{
		*ckpt = 1;
		flag = 1;
	}
	else if (*str == c)
		*ckpt = 0;
	return (flag);
}

static int	count_words(const char *str, char c)
{
	int	words;
	int	ckpt;

	words = 0;
	ckpt = 0;
	while (*str)
	{
		if (flag_ckpt(str, c, &ckpt))
			words++;
		str++;
	}
	return (words);
}

static int	word_setter(char **res, const char **str, char c, int word_index)
{
	int	i;

	i = 0;
	while (**str && **str == c)
		(*str)++;
	while (str[0][i] && str[0][i] != c)
		i++;
	res[word_index] = ft_substr(*str, 0, i);
	if (!res[word_index])
		return (0);
	*str = *str + i + 1;
	return (1);
}

static void	free_words(char ***str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(str[0][j]);
		j++;
	}
	free(*str);
	*str = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	words = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	while (i < words)
	{
		if (!word_setter(res, &s, c, i))
		{
			free_words(&res, i);
			return (NULL);
		}
		i++;
	}
	res[words] = NULL;
	return (res);
}
