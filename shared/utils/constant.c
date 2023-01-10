/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:55:13 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/10 06:41:57 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_word_type_constant
{
	t_wt	*begining;
	t_wt	*greatorless;
	t_wt	*word;
	t_wt	*pipeorif;
	t_wt	*oparenthesis;
	t_wt	*cparenthesis;
	t_wt	*end;
}	t_wtc;

t_wtc	get_next_word_type_consts(t_wtc *wtc)
{
	wtc->begining = alloc(&wtc->begining, 8);
	ft_memcpy((void *)wtc->begining, (const void *){DLESS, LESS, \
		GREAT, DGREAT, WORD, OPRARENTHESIS, END, NULL}, 8);
	wtc->greatorless = alloc(&wtc->greatorless, 2);
	ft_memcpy((void *)wtc->greatorless, (const void *){WORD, NULL}, 2);
	wtc->word = alloc(&wtc->word, 10);
	t_memcpy((void *)wtc->word, (const void *){DLESS, LESS, GREAT, \
		DGREAT, WORD, PIPE, ORIF, ANDIF, END, NULL}, 10);
	wtc->pipeorif = alloc(&wtc->pipeorif, 7);
	t_memcpy((void *)wtc->pipeorif, (const void *){DLESS, LESS, \
	GREAT, DGREAT, WORD, OPRARENTHESIS, NULL}, 7);
	wtc->oparenthesis = alloc(&wtc->oparenthesis, 8);
	t_memcpy((void *)wtc->oparenthesis, (const void *){DLESS, LESS, \
	GREAT, DGREAT, WORD, OPRARENTHESIS, CPARENTHESIS, NULL}, 8);
	wtc->cparenthesis = alloc(&wtc->cparenthesis, 11);
	t_memcpy((void *)wtc->cparenthesis, (const void *){DLESS, LESS, \
	GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, CPARENTHESIS, END, NULL}, 11);
	wtc->end = NULL;
	return (*wtc);
}

t_wtc	get_curr_word_type_consts(t_wtc *wtc)
{
	wtc->begining = NULL;
	wtc->greatorless = alloc(&wtc->greatorless, 8);
	ft_memcpy((void *)wtc->greatorless, (const void *){WORD, PIPE, ORIF, \
		ANDIF, BEGINING, OPRARENTHESIS, CPARENTHESIS, NULL}, 8);
	wtc->word = alloc(&wtc->word, 12);
	t_memcpy((void *)wtc->word, (const void *){DLESS, LESS, GREAT, DGREAT, \
		WORD, PIPE, ORIF, ANDIF,OPRARENTHESIS, CPARENTHESIS, END, NULL}, 12);
	wtc->pipeorif = alloc(&wtc->pipeorif, 3);
	t_memcpy((void *)wtc->pipeorif, (const void *){WORD, \
		CPARENTHESIS, NULL}, 3);
	wtc->oparenthesis = alloc(&wtc->oparenthesis, 6);
	t_memcpy((void *)wtc->oparenthesis, (const void *){PIPE, ORIF, \
	ANDIF, OPRARENTHESIS, BEGINING, NULL}, 6);
	wtc->cparenthesis = alloc(&wtc->cparenthesis, 3);
	t_memcpy((void *)wtc->cparenthesis, (const void *){OPRARENTHESIS, \
		CPARENTHESIS, NULL}, 3);
	wtc->end = alloc(&wtc->end, 4);
	t_memcpy((void *)wtc->end, (const void *){WORD, \
	CPARENTHESIS, BEGINING, NULL}, 4);
	return (*wtc);
}

t_cn	get_according_values(t_wt key)
{
	t_wtc	curr;
	t_wtc	next;
	t_cn	v;

	get_curr_word_type_consts(&curr);
	get_next_word_type_consts(&next);
	if (key == BEGINING)
		return (set_wt_values(curr.begining, next.begining, &v));
	else if (key == LESS || key == DLESS || key == GREAT || key == DGREAT)
		return (set_wt_values(curr.greatorless, next.greatorless, &v));
	else if (key == WORD)
		return (set_wt_values(curr.word, next.word, &v));
	else if (key == PIPE || key == ORIF || key == ANDIF)
		return (set_wt_values(curr.pipeorif, next.pipeorif, &v));
	else if (key == OPRARENTHESIS)
		return (set_wt_values(curr.oparenthesis, next.oparenthesis, &v));
	else if (key == CPARENTHESIS)
		return (set_wt_values(curr.cparenthesis, next.cparenthesis, &v));
	else if (key == END)
		return (set_wt_values(curr.end, next.end, &v));
	else
		return (set_wt_values(curr.end, next.end, &v));
}

t_cn	get_values_of_index(t_wt key, t_kvp *key_values)
{
	int	i;

	i = 0;
	while (key_values[i] != NULL)
	{
		if (key == key_values[i].key)
			return (key_values->values);
		i++;
	}
}

t_kvp	*get_kv_pairs(void)
{
	t_kvp	*keys_values;
	t_wt	*keys;
	int		i;

	keys = alloc(&keys, 13);
	i = 0;
	ft_memcpy(keys, (const void *){BEGINING, DLESS, LESS, \
	GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, OPRARENTHESIS, \
	CPARENTHESIS, END, NULL}, 13);
	keys_values = malloc(sizeof(t_kvp) * 13);
	if (keys_values == NULL)
		return (NULL);
	while (i < 12)
	{
		keys_values[i].key = keys[i];
		keys_values[i].values = get_according_values(keys[i]);
	}
	keys_values[i] = NULL;
	return (keys_values);
}
