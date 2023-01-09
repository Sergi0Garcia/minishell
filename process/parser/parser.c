
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
			handle_beginning(word);
	}
}

void handle_beginning(t_w *word)
{
	t_b is_exist;
	
	is_exist = false;
	is_exist = is_wt_between_values(word->wi.)
}

void handle_end(t_w *word)
{
	t_b is_exist;
}

void check_single_wt(t_wsb wsb)
{
	
}