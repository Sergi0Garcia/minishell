/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:16:33 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/07 05:04:40 by rkanmado         ###   ########.fr       */
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
# include <sys/wait.h>

typedef struct s_redirect
{
	char	**s_filout;
	char	**s_filin;
	char	**d_filout;
	char	**d_filin;
}	t_redirect;

typedef enum s_word_type
{
	COMMAND,
	WORD,
	DIREDIRECT,
	SIREDIRECT,
	SOREDIRECT,
	DOREDIRECT,
	SPACE,
	PIPE,
	AND,
	NEIN
}	t_wt;

typedef enum s_quote
{
	SQUOTE,
	DQUOTE,
	NONE,
}	t_q;

typedef struct s_separator
{
	t_wt	type;
	char	*word;
	t_q		qtype;
}	t_sep;

typedef struct s_command
{
	char	*name;
	char	**args;
	char	**opts;
}	t_c;

typedef enum s_bool
{
	false,
	true,
}	t_b;

typedef struct s_lexing
{
	int			start;
	int			end;
	t_wt		last;
	t_wt		new;
	t_sep		sep;
}	t_lex;

typedef struct s_wordinfo
{
	char	*word;
	t_wt	sep;
	t_b		quoted;
	t_b		expandable;
}	t_wi;

typedef struct s_word
{
	t_wi			wi;
	struct s_word	*next;
	struct s_word	*prev;
}	t_w;

typedef struct s_word_stack_bundle
{
	int				size;
	struct s_word	*head;
	struct s_word	*tail;
}	t_wsb;

typedef struct s_stack_info
{
	char		*raw;
	t_wsb		lsb;
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

typedef struct s_env_node
{
	char				*name;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_minishell
{
	t_line	st;
	char	**env;
	char	**argv;
	char	*pid;
	char	*line;
	t_b		interactive;
	t_wsb	wsb;
	int		status;
}	t_minish;

void		interactive(t_minish *sh);
void		non_interactive(t_minish *sh);

/* shared/utils/parsing */
t_b			is_sep_type(t_wt wt);
t_wt		is_sep(char s1);
int			is_heredoc(char *s1);
void		p_interactive_mode(t_minish *sh);
void		p_noninteractive_mode(t_minish *sh);
void		parse(t_minish *sh);

char		*ft_pwd(char *buffer, int buff_size);
void		set_env(char **envp, t_env_node **env_lst);
void		ft_cd(char *str, t_env_node **env_lst);
void		ft_echo(char **opt, char **arg);
int			is_same_str(char *str1, char *str2);

/* shared/utils/handler.c */
void		h_interactive_mode(t_minish *sh);
void		h_noninteractive_mode(t_minish *sh);
void		handler(t_minish *sh);

/* lst/env */
t_env_node	*ft_env_last(t_env_node *lst);
t_env_node	*ft_new_env_node(char *name, char *value);
void		new_env(t_env_node **env_lst, char *str);
void		unset_env(t_env_node **env_lst, char *str);
int			ft_env_lst_size(t_env_node *lst);
void		print_env(t_env_node **env_lst, int with_declare);
char		*env_value(t_env_node **env_lst, char *name);
void		free_env_node(t_env_node **env);

/* shared/utils/error.c */
void		ft_error(char *str);
void		env_add_back(t_env_node **lst, t_env_node *new);

/* shared/utils/error.c */
void		error(char *str);
t_b			can_add_backtic(char *command);
void		errormsg(char *command, char *text);
char		*joinstrs(char *s1, char *s2);
void		error(char *str);

/* shared/check/check.c */
void		check_usage(int argc, char **argv, t_minish *sh);
void		usage(void);

/* shared/utils/init.c */
void		init(t_minish *sh, char **argv);

/* shared/utils/word_ops.c */
void		ft_wunshift(t_wsb *stack, t_wi info);
void		ft_wpush(t_wsb *stack, t_wi info);
t_wi		ft_wpop(t_wsb *stack);
t_wi		ft_wshift(t_wsb *stack);

/* shared/utils/read */
void		parse(t_minish *sh);
void		read_line(t_minish *sh);

/* shared/utils/utils */
int			ft_strcmp(char *s1, char *s2);
int			end_of_sep(char * str, int start);
t_b			is_sep_type(t_wt wt);
t_wt		is_which_sep(char *s1);
t_wt		is_sep(char s1);

/* shared/utils/handling */
void		handler(t_minish *sh);
void		interactive(t_minish *sh);
void		non_interactive(t_minish *sh);

/* process/signals/signals.c */
void		h_quit(void);
void		sigreset(int sig, siginfo_t *info, void *context);
void		quit(int sig, siginfo_t *info, void *context);
void		interactive_mode_sig(void);
void		no_interactive_mode_sig(void);

/* process/lexer/lexer.c */
t_b			can_hspace(int start, char *str, t_sep *next);
t_b			can_switch(char *substr, t_sep *next);
t_wi		set_winfo(t_sep sep);
void		lexing(t_minish *sh);
void		lexing_with_quote(t_minish *sh, t_lex *lex, t_q *quote);
void		add_new_word(t_lex *lex, t_minish *sh);

/* shared/display/display.c */
void		display_words(t_w *w);
void		init_twsb(t_wsb *wsb);

/* process/lexer/handle_cases */
int			h_bestcase(int start, char *str, t_sep *next);
t_b			is_multi(char *str, char c, t_sep *next);

/* process/quoting/check */
t_b			contain_quote(char *str);
int			end_quote_delimiter(char *str, int i, t_q qtype);
t_b			is_begin_with_quote(char *str);
t_q			is_which_quote(char *str);

#endif
