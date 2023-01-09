#include "../../include/minishell.h"

#define BEGINING_WT (t_wt[]) {DLESS, LESS, GREAT, DGREAT, WORD, OPRARENTHESIS, END}
#define GREATORLESS_WT (t_wt[]) {WORD}
#define WORD_WT (t_wt[]) {DLESS, LESS, GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, END}
#define PIPEORIF_WT (t_wt[]) {DLESS, LESS, GREAT, DGREAT, WORD, OPRARENTHESIS}
#define OPARENTHESIS_WT (t_wt[]) {DLESS, LESS, GREAT, DGREAT, WORD, OPRARENTHESIS, CPARENTHESIS}
#define CPARENTHESIS_WT (t_wt[]) {DLESS, LESS, GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, CPARENTHESIS, END}
#define END_WT (t_wt[]) {WORD, CPARENTHESIS, BEGINING}
#define KEYS (t_wt[]) {BEGINING, DLESS, LESS, GREAT, DGREAT, WORD, PIPE, ORIF, ANDIF, OPRARENTHESIS, CPARENTHESIS, END}

t_wt *get_according_values(t_wt key)
{
	if (key == BEGINING)
		return (BEGINING_WT);
	else if (key == LESS || key == DLESS || key == GREAT || key == DGREAT)
		return (GREATORLESS_WT);
	else if (key == WORD)
		return (WORD_WT);
	else if (key == PIPE || key == ORIF || key == ANDIF)
		return (PIPEORIF_WT);
	else if (key == OPRARENTHESIS)
		return (OPARENTHESIS_WT);
	else if (key == CPARENTHESIS)
		return (CPARENTHESIS_WT);
	else if (key == END)
		return (END_WT);
	else
		return (END_WT);
}

t_kvp   *get_kv_pairs(void)
{
	t_kvp *keys_values;
	int  i;

	keys_values = malloc(sizeof(t_kvp) * 12);
	i = 0;
	while (i < 12)
	{
		keys_values[i].key = KEYS[i];
		keys_values[i].values = get_according_values(KEYS[i]);
	}
	return keys_values;
}
