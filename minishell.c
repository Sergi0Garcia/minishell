/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/05 12:59:50 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minish	sh;
	t_ci		cmd1i;
	t_csb		cmds;

	(void) envp;
	init(&sh, argv);
	check_usage(argc, argv, &sh);
	set_env(envp, &sh.env_lst);
	cmd1i.name = "cd";
	cmd1i.opts = "";
	cmd1i.args = "~/Desktop";
	cmd1i.infile = FD_READ_END;
	cmd1i.outfile = FD_WRITE_END;
	init_tcsb(&cmds);
	ft_cunshift(&cmds, cmd1i);
	sh.cmds = cmds;
	controller(&sh);
	free(sh.cmds.head);
	free_all(&sh, 4);
	return (g_status);
}
