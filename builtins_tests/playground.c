/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 04:57:20 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/23 13:17:40 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int    playground(void)
{
    ft_printf("Playground\n");
    
	// ----------------------
	// ENV PLAYGROUNDs
	// ----------------------
	// ft_printf("------- ENV -------\n\n");
	// char *home;
	// home = env_value(&env_lst, "HOME");
	// printf("Home env var: %s\n", home);
	// unset_env(&env_lst, "HOME");
	// print_env(&env_lst, 0);
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

	int	fd[2];
	
	// initialize pipe
	if (pipe(fd) == -1)
	{
		ft_printf("Error creating pipes\n");
		exit(EXIT_FAILURE);
	}	
	pid_t pid1 = fork();
	if (pid1 < 0)
	{
		ft_printf("Error for process 1\n");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		// Child process
		char *tmp = "c\nb\na\n";
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_printf("%s", tmp);
		return (EXIT_SUCCESS);
	}
	pid_t pid2 = fork();
	if (pid2 < 0)
	{
		ft_printf("Error for process 2\n");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		// Child process 2
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		char	*arg[2];
		// arg[0] = "/bin"
		arg[0] = "/usr/bin/sort";
		arg[1] = NULL;
		printf("execve...\n");
		execve(arg[0], arg, NULL);
		return (EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit(0);
    return (EXIT_SUCCESS);
}