#include "../include/minishell.h"

void init(t_minish *sh, char **argv, char **env)
{
    int i;
    
    i = 0;
    sh->argv = argv;
    sh->pid = ft_atoi(getpid());
    while (env[i++] != NULL)
    sh->env = (char **) malloc((i + 1) * sizeof(char *))
    i = 0;
    while (env[i] != NULL)
    {
        sh->env[i] = ft_strdup(env[i]);
        i++;
    }
    return ;
}