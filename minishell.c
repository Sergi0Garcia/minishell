/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/26 18:38:56 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static char	**parsing_argv(char **argv)
{
	int	len;
	int	i;
	int j;
	char **res;

	len = -1;
	i = 0;
	while (argv[++len]);
	if (len <= 1)
		exit(EXIT_FAILURE);
	res = (char **)malloc(sizeof(char *) * len);
	while (i < len && (argv[i + 1]))
	{
		len = ft_strlen(argv[i + 1]);
		res[i] = (char *)malloc(sizeof(char) * (len + 1));
		j = 0;
		while (j < len)
		{
			res[i][j] = argv[i + 1][j];
			j++;
		}
		res[i][j] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	t_env_node *env_lst;

	// ft_pwd();
	// char **env_vars;
	// ft_cd("..");
	// ft_pwd();

	env_lst = NULL;
	set_env(envp, &env_lst);
	ft_echo(parsing_argv(argv));
	new_env(&env_lst, "TEST=123");
	unset_env(&env_lst, "LESS");
	while (env_lst)
	{
		printf("%s\n", env_lst->name);
		env_lst = env_lst->next;
	}
	return (1);
}
