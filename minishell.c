/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 04:47:31 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <sys/wait.h>

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

	// char	pathname[PATH_MAX];
	// ft_pwd(pathname, PATH_MAX);
	// printf("pathname: %s\n", pathname);

	// ft_cd("..");
	// ft_pwd(pathname, PATH_MAX);
	// printf("pathname: %s\n", pathname);

	char *tmp = "c\nb\na";
	printf("%s\n", tmp);

	pid_t parent = getpid();
	pid_t pid = fork();

	printf("parent pid: %i\n", parent);
	printf("pid: %i\n", pid);

	if (pid > 0)
	{
		int status;
		status = 0;
   		waitpid(pid, &status, 0);
		printf("status: %i\n", status);
		printf("end ...\n");
	}
	else
	{
		char	*arg[3];
		arg[0] = "/bin/ls";
		arg[1] = "-lh";
		arg[2] = NULL;
		printf("execve...\n");
		execve(arg[0], arg, NULL);
	}
	printf("end2 ...\n");
	exit(0);
// 	args[0] = "ls";
// 	args[1] = "-la";
// 	args[2] = "/Users/segarcia/Documents/42/minishell";
// 	args[3] = NULL;
// 	res = execve("/bin/ls", args, NULL);

	env_lst = NULL;
	set_env(envp, &env_lst);
	new_env(&env_lst, "TEST=123");
	unset_env(&env_lst, "SECURITYSESSIONID");
	unset_env(&env_lst, "HOMEBREW_TEMP");
	unset_env(&env_lst, "HOMEBREW_CACHE");
	unset_env(&env_lst, "PWD");
	unset_env(&env_lst, "TEST");
	new_env(&env_lst, "SERGIO00=123");
	while (env_lst)
	{
		printf("~%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
	ft_echo(parsing_argv(argv));
	return (1);
}
