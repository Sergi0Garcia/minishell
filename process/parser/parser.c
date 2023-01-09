
#include "../../include/minishell.h"

void parser(t_minish *sh)
{
	int i;
	t_w *word;
	
	i = 0;
	word = sh->wbs.head;
	while (word != NULL)
	{
		if (i == 0)
			is_edges_good(word);
		else if (i == sh->wbs.size - 1)
			is_edges_good(word);
		else
			is_between_good(word);
	}
}

t_b is_edges_good(t_w *word)
{
	t_b is_exist;
	t_wt *list;

	is_exist = false;
	list = get_according_values(word->wi.sep);
	is_exist = is_wt_between_values(word->wi.sep, list);
	if (is_exist)
		return (true);
	else
		return (false);
}

t_b is_between_good(t_w *word)
{
	t_wt *next;
	t_b is_exist;
	
	// next = 
	return (true);
}

t_b is_according_next_value(t_w word)
{
	t_b is_right_next;
	return (true);
}
