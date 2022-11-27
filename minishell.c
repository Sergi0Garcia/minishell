/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 20:12:22 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <sys/wait.h>

// static char	**parsing_argv(char **argv)
// {
// 	int	len;
// 	int	i;
// 	int j;
// 	char **res;

// 	len = -1;
// 	i = 0;
// 	while (argv[++len]);
// 	if (len <= 1)
// 		exit(EXIT_FAILURE);
// 	res = (char **)malloc(sizeof(char *) * len);
// 	while (i < len && (argv[i + 1]))
// 	{
// 		len = ft_strlen(argv[i + 1]);
// 		res[i] = (char *)malloc(sizeof(char) * (len + 1));
// 		j = 0;
// 		while (j < len)
// 		{
// 			res[i][j] = argv[i + 1][j];
// 			j++;
// 		}
// 		res[i][j] = '\0';
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	t_env_node	*env_lst;

	// ----------------------
	// REQUIRED
	// ----------------------
	env_lst = NULL;
	set_env(envp, &env_lst);

	// ----------------------
	// ECHO
	// ----------------------
	// char	**opt;
	// opt = malloc(sizeof(char *) * (1 + 1));
	// opt[0] = ft_substr("-nnnn", 0, 5);
	// opt[1] = NULL;
	// ft_echo(opt, argv);
	// ----------------------

	// ----------------------
	// PATHNAME && CD
	// ----------------------
	char	pathname[PATH_MAX];
	ft_pwd(pathname, PATH_MAX);
	printf("pathname: %s\n", pathname);
	ft_cd("~/Pictures/", &env_lst);
	ft_pwd(pathname, PATH_MAX);
	printf("pathname: %s\n", pathname);
	// ----------------------

	// ----------------------
	// FORK PLAYGROUND
	// ----------------------
	// char *tmp = "c\nb\na";
	// printf("%s\n", tmp);
	// pid_t parent = getpid();
	// pid_t pid = fork();
	// printf("parent pid: %i\n", parent);
	// printf("pid: %i\n", pid);
	// if (pid > 0)
	// {
	// 	int status;
	// 	status = 0;
   	// 	waitpid(pid, &status, 0);
	// 	printf("status: %i\n", status);
	// 	printf("end ...\n");
	// }
	// else
	// {
	// 	char	*arg[3];
	// 	arg[0] = "/bin/ls";
	// 	arg[1] = "-lh";
	// 	arg[2] = NULL;
	// 	printf("execve...\n");
	// 	execve(arg[0], arg, NULL);
	// }
	// printf("end2 ...\n");
	// exit(0);
	// ----------------------

	// ----------------------
	// FORK PLAYGROUND
	// ----------------------
	// unset_env(&env_lst, "SECURITYSESSIONID");
	// unset_env(&env_lst, "USER");
	// unset_env(&env_lst, "HOMEBREW_TEMP");
	// unset_env(&env_lst, "_");
	// unset_env(&env_lst, "COLORTERM");
	// unset_env(&env_lst, NULL);
	// new_env(&env_lst, "USER=modified");
	print_env(&env_lst, 0);
	// print_env(&env_lst, 1);
	// unset_env(&env_lst, "SECURITYSESSIONID");
	// unset_env(&env_lst, "HOMEBREW_TEMP");
	// unset_env(&env_lst, "HOMEBREW_CACHE");
	// unset_env(&env_lst, "PWD");
	// ft_echo(parsing_argv(argv));
	// ----------------------

	return (1);
}
