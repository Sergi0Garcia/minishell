#include "../../include/minishell.h"

t_b is_wt_between_values(t_wt word_type, t_wt *list)
{
	int i;

	i = 0;
	while (list[i])
	{
		if (word_type == list[i])
			return (true);
	}
	return (false);
}

t_wt	is_which_wt(char *s1)
{
	if (strcmp(s1, "|") == 0)
		return (PIPE);
	else if (strcmp(s1, ">") == 0)
		return (GREAT);
	else if (strcmp(s1, ">>") == 0)
		return (DGREAT);
	else if (strcmp(s1, " ") == 0)
		return (SPACE);
	else if (strcmp(s1, "<") == 0)
		return (LESS);
	else if (strcmp(s1, "<<") == 0)
		return (LESS);
	else if (strcmp(s1, "&") == 0)
		return (ANDIF);
	else if (strcmp(s1, "||") == 0)
		return (ORIF);
	else if (ft_strlen(s1) > 2)
		return (WORD);
	else
		return (NEIN);
}