/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 05:08:15 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/04 22:59:33 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Replace a string with another one */
void	replace_str(char **str, char *to_replace_with, t_lex *lex)
{
	char	*new_str;
	char	*first_range;
	char	*second_range;

	new_str = "";
	first_range = ft_substr(*str, 0, lex->start);
	second_range = ft_substr(*str, (lex->end + lex->start) + 1, \
		end_length(lex, ft_strlen(*str)));
	new_str = ft_strjoin(new_str, first_range);
	new_str = ft_strjoin(new_str, to_replace_with);
	new_str = ft_strjoin(new_str, second_range);
	free(*str);
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

/* Retrieve recursively the variable name if the result is variable */
char	*retrieve_env(char *str, t_env *env_lst)
{
	char	*res1;

	res1 = env_value(&env_lst, str);
	return (res1);
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
