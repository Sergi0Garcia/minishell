/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:21:14 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/29 10:42:40 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	display_words(t_w *w)
{
	while (w != NULL && w->next != NULL)
	{
		printf("word %d, sep %s \n", w->wi.sep, w->wi.word);
		w = w->next;
	}
	printf("word %d, sep %s \n", w->wi.sep, w->wi.word);
	return ;
}
