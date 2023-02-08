/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:55:13 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/08 03:23:01 by rkanmado         ###   ########.fr       */
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

t_wtc	get_curr_word_type_consts(void)
{
	t_wtc	wtc;

	wtc.begining = alloc(&wtc.begining, 8);
	ft_cpywt(&wtc.begining, (const void *)(t_wt[]){DLESS, LESS, \
	GREAT, DGREAT, WORD, OPRARENTHESIS, END, NEIN}, 8);
	wtc.greatorless = alloc(&wtc.greatorless, 2);
	ft_cpywt(&wtc.greatorless, (const void *)(t_wt[]){WORD, NEIN}, 2);
	wtc.word = alloc(&wtc.word, 10);
	ft_cpywt(&wtc.word, (const void *)(t_wt[]){DLESS, LESS, GREAT, \
	DGREAT, WORD, PIPE, ORIF, ANDIF, END, NEIN}, 10);
	wtc.pipeorif = alloc(&wtc.pipeorif, 7);
	ft_cpywt(&wtc.pipeorif, (const void *)(t_wt[]){DLESS, LESS, GREAT, \
	DGREAT, WORD, OPRARENTHESIS, NEIN}, 7);
	wtc.oparenthesis = alloc(&wtc.oparenthesis, 8);
	ft_cpywt(&wtc.oparenthesis, (const void *)(t_wt[]){DLESS, LESS, GREAT, \
	DGREAT, WORD, OPRARENTHESIS, CPARENTHESIS, NEIN}, 8);
	wtc.cparenthesis = alloc(&wtc.cparenthesis, 11);
	ft_cpywt(&wtc.cparenthesis, (const void *)(t_wt[]){DLESS, LESS, GREAT, \
	DGREAT, WORD, PIPE, ORIF, ANDIF, CPARENTHESIS, END, NEIN}, 11);
	wtc.end = alloc(&wtc.end, 1);
	ft_cpywt(&wtc.end, (const void *)(t_wt[]){NEIN}, 1);
	return (wtc);
}

t_wtc	get_next_word_type_consts(void)
{
	t_wtc	wtc;

	wtc.begining = alloc(&wtc.begining, 1);
	ft_cpywt(&wtc.begining, (const void *)(t_wt[]){NEIN}, 1);
	wtc.greatorless = alloc(&wtc.greatorless, 8);
	ft_cpywt(&wtc.greatorless, (const void *)(t_wt[]){WORD, PIPE, ORIF, \
	ANDIF, BEGINING, OPRARENTHESIS, CPARENTHESIS, NEIN}, 8);
	wtc.word = alloc(&wtc.word, 12);
	ft_cpywt(&wtc.word, (const void *)(t_wt[]){DLESS, LESS, GREAT, \
	DGREAT, WORD, PIPE, ORIF, ANDIF, OPRARENTHESIS, CPARENTHESIS, \
	END, NEIN}, 12);
	wtc.pipeorif = alloc(&wtc.pipeorif, 3);
	ft_cpywt(&wtc.pipeorif, (const void *)(t_wt[]){WORD, CPARENTHESIS, \
	NEIN}, 3);
	wtc.oparenthesis = alloc(&wtc.oparenthesis, 6);
	ft_cpywt(&wtc.oparenthesis, (const void *)(t_wt[]){PIPE, ORIF, ANDIF, \
	OPRARENTHESIS, BEGINING, NEIN}, 6);
	wtc.cparenthesis = alloc(&wtc.cparenthesis, 3);
	ft_cpywt(&wtc.cparenthesis, (const void *)(t_wt[]){OPRARENTHESIS, \
	CPARENTHESIS, NEIN}, 3);
	wtc.end = alloc(&wtc.end, 4);
	ft_cpywt(&wtc.end, (const void *)(t_wt[]){WORD, CPARENTHESIS, \
	BEGINING, NEIN}, 4);
	return (wtc);
}

t_cn	get_according_values(t_wt key)
{
	t_wtc	curr;
	t_wtc	next;
	t_cn	v;

	curr = get_curr_word_type_consts();
	next = get_next_word_type_consts();
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
	while (key_values[i].key != NEIN)
	{
		if (key == key_values[i].key)
		{
			cn = (key_values[i].values);
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

	i = 0;
	keys = (t_wt[]){BEGINING, DLESS, LESS, \
	GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, OPRARENTHESIS, \
	CPARENTHESIS, END, NEIN};
	keys_values = (t_kvp *) malloc(sizeof(t_kvp) * 13);
	if (keys_values == NULL)
		return (NULL);
	while (keys[i] != NEIN)
	{
		keys_values[i].key = keys[i];
		keys_values[i].values = get_according_values(keys[i]);
		i++;
	}
	return (keys_values);
}
