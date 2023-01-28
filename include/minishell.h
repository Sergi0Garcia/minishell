/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:16:33 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/28 03:37:46 by rkanmado         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define RESET "\x1B[0m"

# define FD_READ_END 0
# define FD_WRITE_END 1

typedef enum s_word_type
{
	BEGINING,
	WORD,
	DLESS,
	LESS,
	DGREAT,
	GREAT,
	SPACES,
	PIPE,
	ANDIF,
	ORIF,
	OPRARENTHESIS,
	CPARENTHESIS,
	END,
	NEIN
}	t_wt;

typedef struct s_current_and_next_probable_word_type
{
	t_wt	*curr;
	t_wt	*next;
}	t_cn;

typedef struct s_key_value_pair
{
	t_wt	key;
	t_cn	values;
}	t_kvp;

typedef enum s_quote {
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

typedef struct s_command_info
{
	char	*name;
	char	*opts;
	char	*args;
	int		infile;
	int		outfile;
}	t_ci;

typedef struct s_command
{
	t_ci				ci;
	struct s_command	*next;
	struct s_command	*prev;
}	t_c;

typedef struct s_command_bundle
{
	int					size;
	struct s_command	*head;
	struct s_command	*tail;
}	t_csb;

typedef enum s_bool
{
	false,
	true,
}	t_b;

typedef struct s_lexing
{
	size_t		start;
	size_t		end;
	t_b			is_format_ok;
	t_sep		sep;
}	t_lex;

typedef struct s_wordinfo
{
	char	*word;
	t_wt	sep;
	t_q		quote;
	t_b		can_expand;
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
	t_env_node	*env_lst;
	char		**argv;
	char		*pid;
	char		*line;
	t_b			interactive;
	t_wsb		wsb;
	t_csb		cmds;
	int			status;
}	t_minish;

void		interactive(t_minish *sh);
void		non_interactive(t_minish *sh);

/** testing builtins */
void 		tester(t_env_node **env_lst);
int			playground(void);

/** built in functions */
int			cd_valid_flag(t_c *cmd);
void		cd_handle_error(void);
void		ft_export(t_c *cmd, t_env_node **env_lst);
void		ft_unset(t_c *cmd, t_env_node **env_lst);
void		ft_env(t_c *cmd, t_env_node **env_lst);
int			is_same_str(char *str1, char *str2);
int			get_idx_separator(char *str);

/** execution  */
int			controller(t_minish *sh);
int			ft_execve(t_c *cmd, t_env_node **env_lst);
int			ft_path_execve(t_c *cmd, t_env_node **env_lst);
// int			get_fd(char *path, t_wt key);
int			get_fd(void);

/* shared/utils/parsing */
t_b			is_sep_type(t_wt wt);
t_wt		is_sep(char s1);
int			is_heredoc(char *s1);
void		p_interactive_mode(t_minish *sh);
void		p_noninteractive_mode(t_minish *sh);
void		parse(t_minish *sh);

char		*ft_pwd(t_c *cmd);
void		set_env(char **envp, t_env_node **env_lst);
void		ft_cd(t_c *cmd, t_env_node **env_lst);
void		ft_echo(t_c *cmd);
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
int			exists_env(t_env_node **env_lst, char *str);

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
void		init_tcsb(t_csb *cmds);
void		init_twsb(t_wsb *wsb);

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
int			end_of_sep(char *str, int start);
t_b			is_sep_type(t_wt wt);
char		*char_of_sep(t_wt wt);
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
void		lexing_without_quote(t_minish *sh, t_lex *lex, t_b *is_quoted);
void		add_new_word(t_lex *lex, t_minish *sh);

/* process/lexer/utils */
void		remove_spaces(t_minish *sh);
void		check_greatorless(t_wt *last, char *str);
void		end_token_delimiter(char *str, t_lex *lex);
void		escape_spaces(char *str, t_lex *lex);

/* shared/display/display.c */
void		display_words(t_w *w);

/* process/lexer/handle_cases */
int			h_bestcase(int start, char *str, t_sep *next);
t_b			is_multi(char *str, char c, t_sep *next);

/* process/quoting/check */
void		recursive_rl(t_minish *sh, t_lex *lex, char *title);
int			end_quote_delimiter(char *str, t_lex *lex, char c);
t_b			is_begin_with_quote(char *str);
t_q			is_which_quote(char *str);

/* process/parser/check.c */
t_b			is_wt_between_values(t_wt word_type, t_wt *list);
t_wt		is_which_wt(char *s1);

/* process/parser/parser.c */
t_b			parser(t_minish *sh);
t_b			is_begin_good(t_w *word, t_kvp *kvp, t_b *can_continue);
t_b			is_end_good(t_w *word, t_kvp *kvp, t_b *can_continue);
t_b			is_between_good(t_w *word, t_kvp *kvp, t_b *can_continue);

/* process/parser/error.c */
void		parser_error(char *str);

/* process/shared/utils/constants.c */
t_cn		get_according_values(t_wt key);
t_kvp		*get_kv_pairs(void);
t_cn		set_wt_values(t_wt *curr, t_wt *next, t_cn *cn);
t_cn		get_values_of_index(t_wt key, t_kvp *key_values);

/* process/shared/utils/alloc.c */
t_wt		*alloc(t_wt	**wt, int mem_nbr);
void		*ft_cpywt(void *dst, const void *src, size_t n);

/* process/expansion/expansion.c */
void		expansion(t_minish *sh);
void		expansion_process(char **str);
void		expand_var(char **str, size_t start);
void		end_of_expandation(char *str, size_t *end);

/* process/expansion/utils.c */
void		replace_str(char **str, char *to_replace_with, t_lex *lex);
t_b			can_apply_expansion(char **str);
size_t		end_length(t_lex *lex, size_t strlen);
char		*retrieve_env(char *str);

/* process/utils/free.c */
void		free_str(char **str);
void		free_stack(t_w **head, t_w **tail);

/* process/command/command.c */
void		generate_cmd(t_minish *sh);
void		add_to_chunk(t_wsb *chunk, t_wi wi);
void		handle_pipe_found(t_csb *list, t_wsb *wsb);
void		parse_wsb_to_cmd(t_csb *list, t_wsb *wsb);
void		add_to_cmd(t_w **head, t_ci *ci);

/* process/command/utils.c */
t_b			is_opt_already_exits(t_wsb *wsb, char *opt);
t_b			is_option(char *opt);

/* utils/s_cmd_ops.c */
void		ft_cunshift(t_csb *stack, t_ci info);
void		ft_cpush(t_csb *stack, t_ci info);
t_ci		ft_cpop(t_csb *stack);
t_ci		ft_cshift(t_csb *stack);

#endif
