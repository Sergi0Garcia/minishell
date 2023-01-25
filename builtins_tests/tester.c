/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 04:15:21 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/25 03:31:14 by rkanmado         ###   ########.fr       */
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
	// fd = get_fd("./testing/output.txt", DGREAT);
	// printf("fd: %i\n", fd);

	cmd1 = malloc(sizeof(t_c));
	cmd1->name = ft_strdup("dasfadsjkfhajsh");
	cmd1->opts = NULL;
	cmd1->args = NULL;
	cmd1->infile = FD_READ_END;
	cmd1->outfile = FD_WRITE_END;

	cmd2 = malloc(sizeof(t_c));
	cmd2->name = ft_strdup("sort");
	cmd2->opts = NULL;
	cmd2->args = NULL;
	cmd2->infile = FD_READ_END;
	cmd2->outfile = FD_WRITE_END;

	t_c *command;
	char	**optstr;
	char	**argstr;



	command = NULL;
	command = malloc(sizeof(t_c));
	command->ci.name = name;
	optstr = opts_array;
	argstr = args_array;
	// optstr = ft_split(command->ci.opts, ' ');
	// argstr = ft_split(command->ci.args, ' ');
	printf(KMAG "---------------------- \n");
	printf(KMAG "L[%i] - name: %s\n", (int)ft_strlen(command->ci.name), command->ci.name);
	i = 0;
	while (optstr && optstr[i])
	{
		printf("L[%i] - opts: %s\n", (int)ft_strlen( optstr[i]), optstr[i]);
		i++;
	}
	i = 0;
	while (argstr && argstr[i])
	{
		printf("L[%i] - args: %s\n", (int)ft_strlen( argstr[i]), argstr[i]);
		i++;
	}
	printf(KMAG "---------------------- \n");
	printf(KRED "---------------------- \n");

	if (is_same_str(command->ci.name, "echo"))
		ft_echo(command);
	else if (is_same_str(command->ci.name, "cd"))
		ft_cd(command, &env_lst);
	else if (is_same_str(command->ci.name, "pwd"))
		ft_pwd(command);
	else if (is_same_str(command->ci.name, "export"))
	{
		ft_export(command, &env_lst);
		if (argstr)
			ft_export(NULL, &env_lst);
	}
	else if (is_same_str(command->ci.name, "unset"))
	{
		printf(KMAG "---------------------- \n");
		ft_export(NULL, &env_lst);
		printf(KMAG "---------------------- \n" RESET);
		ft_unset(command, &env_lst);
		printf(KRED "---------------------- \n");
		ft_export(NULL, &env_lst);
		printf(KRED "---------------------- \n" RESET);
	}
	else if (is_same_str(command->ci.name, "env"))
	{
		ft_env(command, &env_lst);
	}
	else
		ft_execve(&env_lst, command);

	printf(KRED "---------------------- \n");
}
