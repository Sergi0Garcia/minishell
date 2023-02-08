/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:55:13 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/07 07:05:02 by rkanmado         ###   ########.fr       */
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

t_wtc	get_curr_word_type_consts(t_wtc *wtc)
{
	wtc->begining = (t_wt[]){DLESS, LESS, GREAT, DGREAT, WORD, OPRARENTHESIS, \
	END, NEIN};
	wtc->greatorless = (t_wt[]){WORD, NEIN};
	wtc->word = (t_wt[]){DLESS, LESS, GREAT, DGREAT, WORD, PIPE, ORIF, \
	ANDIF, END, NEIN};
	wtc->pipeorif = (t_wt[]){DLESS, LESS, GREAT, DGREAT, WORD, OPRARENTHESIS, \
	NEIN};
	wtc->oparenthesis = (t_wt[]){DLESS, LESS, GREAT, DGREAT, WORD, \
	OPRARENTHESIS, CPARENTHESIS, NEIN};
	wtc->cparenthesis = (t_wt[]){DLESS, LESS, GREAT, DGREAT, WORD, PIPE, ORIF, \
	ANDIF, CPARENTHESIS, END, NEIN};
	wtc->end = (t_wt[]){NEIN};
	return (*wtc);
}

t_wtc	get_next_word_type_consts(t_wtc *wtc)
{
	wtc->begining = (t_wt[]){NEIN};
	wtc->greatorless = (t_wt[]){WORD, PIPE, ORIF, ANDIF, BEGINING, \
	OPRARENTHESIS, CPARENTHESIS, NEIN};
	wtc->word = (t_wt[]){DLESS, LESS, GREAT, DGREAT, WORD, PIPE, ORIF, \
	ANDIF, OPRARENTHESIS, CPARENTHESIS, END, NEIN};
	wtc->pipeorif = (t_wt[]){WORD, CPARENTHESIS, NEIN};
	wtc->oparenthesis = (t_wt[]){PIPE, ORIF, ANDIF, OPRARENTHESIS, BEGINING, \
	NEIN};
	wtc->cparenthesis = (t_wt[]){OPRARENTHESIS, CPARENTHESIS, NEIN};
	wtc->end = (t_wt[]){WORD, CPARENTHESIS, BEGINING, NEIN};
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
