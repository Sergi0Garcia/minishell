/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:55:13 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/11 07:27:01 by rkanmado         ###   ########.fr       */
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
	ft_cpywt((void *)wtc->begining, (const void *)(t_wt[]){DLESS, LESS, \
		GREAT, DGREAT, WORD, OPRARENTHESIS, END}, 7);
	wtc->greatorless = alloc(&wtc->greatorless, 1);
	ft_cpywt((void *)wtc->greatorless, (const void *)(t_wt[]){WORD}, 1);
	wtc->word = alloc(&wtc->word, 9);
	ft_cpywt((void *)wtc->word, (const void *)(t_wt[]){DLESS, LESS, GREAT, \
		DGREAT, WORD, PIPE, ORIF, ANDIF, END}, 9);
	wtc->pipeorif = alloc(&wtc->pipeorif, 6);
	ft_cpywt((void *)wtc->pipeorif, (const void *)(t_wt[]){DLESS, LESS, \
	GREAT, DGREAT, WORD, OPRARENTHESIS}, 6);
	wtc->oparenthesis = alloc(&wtc->oparenthesis, 7);
	ft_cpywt((void *)wtc->oparenthesis, (const void *)(t_wt[]){DLESS, LESS, \
	GREAT, DGREAT, WORD, OPRARENTHESIS, CPARENTHESIS}, 7);
	wtc->cparenthesis = alloc(&wtc->cparenthesis, 10);
	ft_cpywt((void *)wtc->cparenthesis, (const void *)(t_wt[]){DLESS, LESS, \
	GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, CPARENTHESIS, END}, 10);
	wtc->end = NULL;
	return (*wtc);
}

t_wtc	get_curr_word_type_consts(t_wtc *wtc)
{
	wtc->begining = NULL;
	wtc->greatorless = alloc(&wtc->greatorless, 7);
	ft_cpywt((void *)wtc->greatorless, (const void *)(t_wt[]){WORD, \
	PIPE, ORIF, ANDIF, BEGINING, OPRARENTHESIS, CPARENTHESIS}, 7);
	wtc->word = alloc(&wtc->word, 11);
	ft_cpywt((void *)wtc->word, (const void *)(t_wt[]){DLESS, LESS, \
	GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, OPRARENTHESIS, CPARENTHESIS, \
	END}, 11);
	wtc->pipeorif = alloc(&wtc->pipeorif, 2);
	ft_cpywt((void *)wtc->pipeorif, (const void *)(t_wt[]){WORD, \
		CPARENTHESIS}, 2);
	wtc->oparenthesis = alloc(&wtc->oparenthesis, 5);
	ft_cpywt((void *)wtc->oparenthesis, (const void *)(t_wt[]){PIPE, ORIF, \
	ANDIF, OPRARENTHESIS, BEGINING}, 5);
	wtc->cparenthesis = alloc(&wtc->cparenthesis, 2);
	ft_cpywt((void *)wtc->cparenthesis, (const void *)(t_wt[]){OPRARENTHESIS, \
		CPARENTHESIS}, 2);
	wtc->end = alloc(&wtc->end, 3);
	ft_cpywt((void *)wtc->end, (const void *)(t_wt[]){WORD, \
	CPARENTHESIS, BEGINING}, 3);
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
	int		i;
	t_cn	cn;

	i = 0;
	cn.curr = NULL;
	cn.next = NULL;
	while (i < 12)
	{
		if (key == key_values[i].key)
		{
			cn = (key_values->values);
			break ;
		}
		i++;
	}
	return (cn);
}

t_kvp	*get_kv_pairs(void)
{
	t_kvp	*keys_values;
	t_wt	*keys;
	int		i;

	alloc(&keys, 12);
	i = 0;
	ft_cpywt((void *)keys, (const void *)(t_wt[]){BEGINING, DLESS, LESS, \
	GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, OPRARENTHESIS, \
	CPARENTHESIS, END}, 12);
	keys_values = malloc(sizeof(t_kvp) * 12);
	if (keys_values == NULL)
		return (NULL);
	while (i < 12)
	{
		keys_values[i].key = keys[i];
		keys_values[i].values = get_according_values(keys[i]);
		i++;
	}
	return (keys_values);
}
