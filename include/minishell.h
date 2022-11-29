/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:16:33 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/29 03:51:29 by segarcia         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/wait.h>

typedef struct s_redirect
{
	char	**s_filout;
	char	**s_filin;
	char	**d_filout;
	char	**d_filin;
}	t_redirect;

typedef struct s_line_stack_info
{
	char				*command;
	int					*sep;
	char				*opts;
	char				*args;
	struct s_redirect	*red;
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
	bool	interactive;
	int		status;
}	t_minish;

void	interactive(t_minish *sh);
void	non_interactive(t_minish *sh);
typedef struct s_env_node
{
	char				*name;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;
/* extern/utils/parsing */
int		is_sep(char *s1);
int		is_heredoc(char *s1);
void	p_interactive_mode(t_minish *sh);
void	p_noninteractive_mode(t_minish *sh);
void	parse(t_minish *sh);

char	*ft_pwd(char *buffer, int buff_size);
void	set_env(char **envp, t_env_node **env_lst);
void	ft_cd(char *str, t_env_node **env_lst);
void	ft_echo(char **opt, char **arg);
int		is_same_str(char *str1, char *str2);
/* extern/utils/handler.c */
void	h_interactive_mode(t_minish *sh);
void	h_noninteractive_mode(t_minish *sh);
void	handler(t_minish *sh);

/* lst/env */
t_env_node	*ft_env_last(t_env_node *lst);
t_env_node	*ft_new_env_node(char *name, char *value);
void		new_env(t_env_node **env_lst, char *str);
void		unset_env(t_env_node **env_lst, char *str);
int			ft_env_lst_size(t_env_node *lst);
void		print_env(t_env_node **env_lst, int	with_declare);
char		*env_value(t_env_node **env_lst,char *name);
void		free_env_node(t_env_node **env);

/* zxterns/utils/error.c */
void	ft_error(char *str);
void	env_add_back(t_env_node **lst, t_env_node *new);
/* externs/utils/error.c */
void	error(char *str);
void	check_usage(int argc, char **argv, t_minish *sh);
void	usage(void);

/* externs/utils/init.c */
void	init(t_minish *sh, char **argv, char **env);

/* externs/utils/line_ops.c */
void	ft_unshift_line(t_lsb *stack, t_sli info);
void	ft_push_line(t_lsb *stack, t_sli info);
t_sli	ft_pop_line(t_lsb *stack);
t_sli	ft_shift_line(t_lsb *stack);

/* extern/utils/read */
void	parse(t_minish *sh);
void	read_line(t_minish *sh);

/* extern/utils/utils */
int		ft_strcmp(char *s1, char *s2);

/* extern/utils/handling */
void	handler(t_minish *sh);
void	interactive(t_minish *sh);
void	non_interactive(t_minish *sh);

/* extern/signals/signals */
void	h_quit(void);
void	sigreset(int sig, siginfo_t *info, void *context);
void	quit(int sig, siginfo_t *info, void *context);
void	interactive_mode_sig(void);
void	no_interactive_mode_sig(void);

#endif
