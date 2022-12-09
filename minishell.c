/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2022/12/09 11:32:38 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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

// void	interactive(t_minish *sh)
// {
// 	read_line(sh);
// 	parse(sh);
// 	return ;
// }

// void	non_interactive(t_minish *sh)
// {
// 	parse(sh);
// 	return ;
// }

int	main(int argc, char **argv, char **envp)
{
	t_minish	sh;

	(void) sh;
	(void) argc;
	(void) argv;
	(void) envp;

	// check_usage(argc, argv, &sh);
	// init(&sh, argv, envp);
	// check_usage(argc, argv, &sh);
	// handler(&sh);
	// ----------------------
	// REQUIRED
	// ----------------------
	t_env_node	*env_lst;
	env_lst = NULL;
	set_env(envp, &env_lst);
	echo_test(env_lst);
	// echo -n functio

	// ----------------------
	// ECHO
	// ----------------------
	// ft_printf("------- ECHO -------\n\n");
	// char	**opt;
	// opt = malloc(sizeof(char *) * (1 + 1));
	// ft_echo(NULL, argv);
	// opt[0] = ft_substr("-nnnn", 0, 5);
	// opt[1] = NULL;
	// ft_echo(opt, argv);
	// opt[0] = ft_substr("-", 0, 5);
	// ft_echo(opt, argv);
	// opt[0] = ft_substr("-nana", 0, 5);
	// ft_echo(opt, argv);
	// ft_printf("\n\n");
	// ----------------------

	// ----------------------
	// PATHNAME && CD
	// ----------------------
	// ft_printf("------- PATHNAME & CD -------\n\n");
	// char	pathname[PATH_MAX];

	// ft_pwd(pathname, PATH_MAX);
	// printf("pathname: %s\n", pathname);
	// ft_cd("~/Desktop", &env_lst);
	// ft_pwd(pathname, PATH_MAX);
	// printf("pathname: %s\n", pathname);
	// ft_cd("-", &env_lst);
	// ft_pwd(pathname, PATH_MAX);
	// printf("pathname: %s\n", pathname);
	// ft_cd("-LPLPLPLPDSDWJWQ Hello", &env_lst);
	// ft_pwd(pathname, PATH_MAX);
	// printf("pathname: %s\n", pathname);
	// ----------------------

	// ----------------------
	// FORK PLAYGROUND
	// ----------------------

	// int	fd[2];

	// // initialize pipe
	// if (pipe(fd) == -1)
	// {
	// 	ft_printf("Error creating pipes\n");
	// 	exit(EXIT_FAILURE);
	// }
	// pid_t pid1 = fork();
	// if (pid1 < 0)
	// {
	// 	ft_printf("Error for process 1\n");
	// 	exit(EXIT_FAILURE);
	// }
	// if (pid1 == 0)
	// {
	// 	// Child process
	// 	char *tmp = "c\nb\na\n";
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	ft_printf("%s", tmp);
	// 	char	*ptr;
	// 	ptr = ft_pwd(NULL);
	// 	printf("%s\n", ptr);
	// 	return (EXIT_SUCCESS);
	// }
	// pid_t pid2 = fork();
	// if (pid2 < 0)
	// {
	// 	ft_printf("Error for process 2\n");
	// 	exit(EXIT_FAILURE);
	// }
	// if (pid2 == 0)
	// {
	// 	// Child process 2
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	char	*arg[2];
	// 	arg[0] = "/usr/bin/sort";
	// 	arg[1] = NULL;
	// 	printf("execve...\n");
	// 	execve(arg[0], arg, NULL);
	// 	return (EXIT_SUCCESS);
	// }
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	// exit(0);

	// ----------------------
	// ----------------------
	// ENV PLAYGROUND
	// ----------------------
	// ft_printf("------- ENV -------\n\n");
	// char *home;
	// home = env_value(&env_lst, "HOME");
	// printf("Home env var: %s\n", home);
	// print_env(&env_lst, 0);
	// unset_env(&env_lst, "HOME");
	// printf("Home env var: %s\n", home);
	// unset_env(&env_lst, "SECURITYSESSIONID");
	// unset_env(&env_lst, "USER");
	// unset_env(&env_lst, "HOMEBREW_TEMP");
	// unset_env(&env_lst, "_");
	// unset_env(&env_lst, "COLORTERM");
	// unset_env(&env_lst, NULL);
	// new_env(&env_lst, "USER=modified");
	// print_env(&env_lst, 0);
	// print_env(&env_lst, 1);
	// unset_env(&env_lst, "SECURITYSESSIONID");
	// unset_env(&env_lst, "HOMEBREW_TEMP");
	// unset_env(&env_lst, "HOMEBREW_CACHE");
	// unset_env(&env_lst, "PWD");
	// ft_echo(parsing_argv(argv));
	// ----------------------

	// char *res;

	// res = env_value(&env_lst, "HOME8472349872843289");
	// printf("%s\n", res);
	// new_env(&env_lst, "HOME=modified");
	// res = env_value(&env_lst, "HOME");
	// printf("%s\n", res);

	return (1);
}
