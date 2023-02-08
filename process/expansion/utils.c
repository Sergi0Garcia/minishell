/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 05:08:15 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/08 06:59:42 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strcat2(char *s1, char *s2)
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

/* Replace a string with another one */
void	replace_str(char **str, char *to_replace_with, t_lex *lex)
{
	char	*new_str;
	char	*first_range;
	char	*second_range;

	first_range = ft_substr(*str, 0, lex->start);
	second_range = ft_substr(*str, (lex->end + lex->start) + 1, \
		end_length(lex, ft_strlen(*str)));
	new_str = malloc(sizeof(char) * ft_strlen(first_range) + \
		ft_strlen(second_range) + ft_strlen(to_replace_with) + 1);
	*new_str = '\0';
	new_str = ft_strcat2(new_str, first_range);
	new_str = ft_strcat2(new_str, to_replace_with);
	new_str = ft_strcat2(new_str, second_range);
	free(*str);
	free(second_range);
	free(first_range);
	*str = new_str;
	lex->start += ft_strlen(to_replace_with);
	return ;
}

/* This function helps us to delimitate the length of the string
*  to replace by the env variable for exemple
*/
size_t	end_length(t_lex *lex, size_t strlen)
{
	if (strlen == (lex->end + lex->start) + 1)
		return (0);
	else
		return (strlen - lex->end);
}

/* Retrieve the env */
char	*get_env(char *str)
{
	(void) str;
	return ("Traky");
}

/* This function checks if the expansion can be applied */
t_b	can_apply_expansion(char **str)
{
	char	*tmp;

	tmp = *str;
	if (ft_strlen(tmp) == 1)
		return (false);
	else if (*(tmp + 1) == '\"' || *(tmp + 1) == '\'')
		return (false);
	return (true);
}
