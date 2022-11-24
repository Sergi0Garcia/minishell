/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:16:33 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/24 16:55:49 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf/include/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_line_stack_info
{
	char	*command;
	int		*sep;
	char	*args;
}	t_sli;

typedef struct s_line_stack
{
	t_sli				li;
	struct s_line_stack	*next;
	struct s_line_stack	*prev;
}	t_ls;

typedef struct s_line_stack_bundle
{
	int					size;
	struct s_line_stack	*head;
	struct s_line_stack	*tail;
}	t_lsb;

typedef struct s_stack_info
{
	char		*raw;
	t_lsb		lsb;
}	t_si;

typedef struct s_line
{
	t_si			si;
}	t_line;

typedef struct s_stack_bundle
{
	int				size;
	struct s_stack	*head;
	struct s_stack	*tail;
}	t_sb;

typedef struct s_minishell
{
	t_line	st;
	char	**env;
	char	**argv;
	char	*pid;
	char	*line;
}	t_minish;

int		ft_pwd(void);
char	**set_env(char **envp);
void	ft_cd(char *str);
void	ft_echo(char **arg);

/* zxterns/utils/error.c */
void	ft_error(char *str);

/* externs/utils/init.c */
void	init(t_minish *sh, char **argv, char **env);

/* externs/utils/line_ops.c */
void	ft_unshift_line(t_lsb *stack, t_sli info);
void	ft_push_line(t_lsb *stack, t_sli info);
t_sli	ft_pop_line(t_lsb *stack);
t_sli	ft_shift_line(t_lsb *stack);

/* extern/utils/read */
void	parse(t_minish *sh);

#endif
