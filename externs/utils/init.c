#include "../../include/minishell.h"

void init(t_minish *sh, char **argv, char **env)
{
    int i;
    pid_t	pid;
    char    *str;

    i = 0;
    sh->argv = argv;
    pid = getpid();
    str = ft_itoa(pid);
    sh->pid = str;
    while (env[i++] != NULL)
    sh->env = (char **) malloc((i + 1) * sizeof(char *));
    i = 0;
    while (env[i] != NULL)
    {
        sh->env[i] = ft_strdup(env[i]);
        i++;
    }
    return ;
}