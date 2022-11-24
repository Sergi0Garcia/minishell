/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/24 14:27:57 by segarcia         ###   ########.fr       */
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
	// ft_pwd();
	// char **env_vars;
	// env_vars = set_env(envp);
	// ft_cd("..");
	// ft_pwd();
	ft_echo(parsing_argv(argv));
	return (1);
}
