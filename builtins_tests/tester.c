/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 04:15:21 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/27 02:29:51 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void tester(t_env_node **env_lst)
{
	(void) 	env_lst;
	
	t_c *cmd1;
	t_c	*cmd2;
	t_c *cmd3;

	// int fd;
	// fd = get_fd("tmp.txt", LESS);
	// printf("fd: %i\n", fd);

	cmd1 = malloc(sizeof(t_c));
	cmd1->name = ft_strdup("unset");
	cmd1->opts = NULL;
	cmd1->args = ft_split("TMP=123", ' ');
	cmd1->infile = FD_READ_END;
	cmd1->outfile = FD_WRITE_END;

	cmd2 = malloc(sizeof(t_c));
	cmd2->name = ft_strdup("sort");
	cmd2->opts = NULL;
	cmd2->args = NULL;
	cmd2->infile = FD_READ_END;
	cmd2->outfile = FD_WRITE_END;

	cmd3 = malloc(sizeof(t_c));
	cmd3->name = ft_strdup("sort");
	cmd3->opts = NULL;
	cmd3->args = NULL;
	cmd3->infile = FD_READ_END;
	cmd3->outfile = FD_WRITE_END;

	cmd1->next = cmd2;
	cmd2->next = NULL;
	cmd3->next = NULL;

	printf("minishell_out: %i\n", controller(cmd1, env_lst));
	ft_export(NULL, env_lst);
	
	// char	name[256];
	// char	options[256];
	// char	arguments[256];

	// char	**opts_array;
	// char	**args_array;
	// int		args;
	// int		opts;
	// int		i;

	// i = 0;
	// args = 0;
	// opts = 0;
	// opts_array = NULL;
	// args_array = NULL;

	// printf(KGRN "---------------------- \n" RESET);
	// printf(KGRN "	TESTER   \n" RESET);
	// printf(KGRN "---------------------- \n" RESET);
	// printf(KCYN "---------------------- \n" RESET);
	// printf(KCYN "Enter name: " RESET);
	// fscanf(stdin,"%s", name);
	// printf(KCYN "Enter options number: " RESET);
	// fscanf(stdin,"%i", &opts);
	// if (opts > 0)
	// {
	// 	i = 0;
	// 	opts_array = malloc(sizeof(char *) * (opts + 1));
	// 	while (i < opts)
	// 	{
	// 		printf(KCYN "opt[%i]: ", i);
	// 		printf(RESET);
	// 		fscanf(stdin,"%s", options);
	// 		opts_array[i] = ft_strdup(options);
	// 		i++;
	// 	}
	// 	opts_array[i] = NULL;
	// }
	// printf(KCYN "Enter args number: " RESET);
	// fscanf(stdin,"%i", &args);
	// if (args > 0)
	// {
	// 	i = 0;
	// 	args_array = malloc(sizeof(char *) * (args + 1));
	// 	while (i < args)
	// 	{
	// 		printf(KCYN "arg[%i]: ", i);
	// 		printf(RESET);
	// 		fscanf(stdin,"%s", arguments);
	// 		args_array[i] = ft_strdup(arguments);
	// 		i++;
	// 	}
	// 	args_array[i] = NULL;
	// }
	// printf(KCYN "---------------------- \n" RESET);

	// t_c *command;

	// command = NULL;
	// command = malloc(sizeof(t_c));
	// command->name = name;
	// command->opts = opts_array;
	// command->args = args_array;
	// printf(KMAG "---------------------- \n");
	// printf(KMAG "L[%i] - name: %s\n", (int)ft_strlen(command->name), command->name);
	// i = 0;
	// while (command->opts && command->opts[i])
	// {
	// 	printf("L[%i] - opts: %s\n", (int)ft_strlen( command->opts[i]), command->opts[i]);
	// 	i++;
	// }
	// i = 0;
	// while (command->args && command->args[i])
	// {
	// 	printf("L[%i] - args: %s\n", (int)ft_strlen( command->args[i]), command->args[i]);
	// 	i++;
	// }
	// printf(KMAG "---------------------- \n");
	// printf(KRED "---------------------- \n");
	
	// if (is_same_str(command->name, "echo"))
	// 	ft_echo(command);
	// else if (is_same_str(command->name, "cd"))
	// 	ft_cd(command, &env_lst);
	// else if (is_same_str(command->name, "pwd"))
	// 	ft_pwd(command);
	// else if (is_same_str(command->name, "export"))
	// {
	// 	ft_export(command, &env_lst);
	// 	if (command->args)
	// 		ft_export(NULL, &env_lst);
	// }
	// else if (is_same_str(command->name, "unset"))
	// {
	// 	printf(KMAG "---------------------- \n");
	// 	ft_export(NULL, &env_lst);
	// 	printf(KMAG "---------------------- \n" RESET);
	// 	ft_unset(command, &env_lst);
	// 	printf(KRED "---------------------- \n");
	// 	ft_export(NULL, &env_lst);
	// 	printf(KRED "---------------------- \n" RESET);
	// }
	// else if (is_same_str(command->name, "env"))
	// {
	// 	ft_env(command, &env_lst);
	// }
	// else 
	// 	ft_execve(&env_lst, command);
	// printf(KRED "---------------------- \n");
}