/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:16:33 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/09 06:36:45 by rkanmado         ###   ########.fr       */
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
# include <termios.h>

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

typedef enum s_error_type
{
	ERR_NONE,
	ERR_PIPE,
	ERR_FORK,
	ERR_PATH,
	ERR_CMD_FOUND,
	ERR_DUP2,
	ERR_PERMISSION,
	ERR_IS_DR,
	ERR_NUM_ARG,
	ERR_EXIT_MARG,
}	t_err;

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
}	t_env;

typedef struct s_word_type_constant
{
	t_wt	*begining;
	t_wt	*greatorless;
	t_wt	*word;
	t_wt	*pipeorif;
	t_wt	*oparenthesis;
	t_wt	*cparenthesis;
	t_wt	*end;
}	t_wtc;

typedef struct s_minishell
{
	t_env		*env_lst;
	char		**argv;
	char		*pid;
	t_kvp		*kvp;
	char		*line;
	t_b			interactive;
	t_wsb		wsb;
	t_wi		last;
	t_csb		cmds;
	int			status;
}	t_minish;

void		interactive(t_minish *sh);
void		non_interactive(t_minish *sh);

/** testing builtins */
void		tester(t_env **env_lst);
int			playground(void);

/** built in functions */
int			cd_valid_flag(t_c *cmd);
int			cd_handle_error(void);
int			ft_export(t_ci cmd, t_env **env_lst);
int			ft_unset(t_ci cmd, t_env **env_lst);
int			ft_env(t_ci cmd, t_env **env_lst);
int			is_same_str(char *str1, char *str2);
int			get_idx_separator(char *str);
void		free_array(char **str);
int			c_child(char **str);
char		**split_paths(char *path);
int			return_free(char **opts, int st);
int			is_single_cmd(t_c *cmd);
int			is_single_execution(t_c *cmd);
void		cd_def_free(char *s1, char *s2, char *s3);
int			define_home_path(char **args);
char		*free_return_args(char **args, char *res);
void		free_env_list(t_env **env_lst);

/** execution  */
int			controller(t_minish *sh);
int			is_single_cmd(t_c *cmd);
int			is_single_execution(t_c *cmd);
int			is_file(char *str);
int			file_validation(char *path);
int			ft_execve(t_ci cmd, t_env **env_lst, int path_exec);
int			get_fd(char *path, t_wt key, int *i);
t_b			handle_here_doc(char *eof, int fd);
int			ci_error(t_err type, int err);
char		*cs_error(t_err type, int err);
char		*get_cmd_path(t_env **env_lst, char *str);
int			valid_fork(t_c *cmds, t_env **env_lst);
int			fd_less(char *path);
int			fd_great(char *path);
int			fd_dgreat(char *path);
void		sig_quit_from_child(int sig, siginfo_t *info, void *context);
void		sig_int(void);
void		dbl_exec_free(char **opts, char **args);
char		**set_opts_exec(t_ci cmd);
char		**set_args_exec(t_ci cmd);
int			cdb_fret(char *path, char *old_path);

/* shared/utils/parsing */
t_b			is_sep_type(t_wt wt);
t_wt		is_sep(char s1);
int			is_heredoc(char *s1);
void		p_interactive_mode(t_minish *sh);
void		p_noninteractive_mode(t_minish *sh);
void		parse(t_minish *sh);

char		*ft_pwd(t_c *cmd, int print);
void		set_env(char **envp, t_env **env_lst);
int			ft_cd(t_c *cmd, t_env **env_lst);
int			ft_echo(t_ci cmd);
int			is_same_str(char *str1, char *str2);

/* shared/utils/handler.c */
void		h_interactive_mode(t_minish *sh);
void		h_noninteractive_mode(t_minish *sh);
void		handler(t_minish *sh);

/* shared/utils/free2.c */
char		**free_dp(char ***points);

/* lst/env */
t_env		*ft_env_last(t_env *lst);
t_env		*ft_new_env_node(char *name, char *value);
void		new_env(t_env **env_lst, char *str);
void		unset_env(t_env **env_lst, char *str);
int			ft_env_lst_size(t_env *lst);
void		print_env(t_env **env_lst, int with_declare);
char		*env_value(t_env **env_lst, char *name);
void		free_env_node(t_env **env);
int			exists_env(t_env **env_lst, char *str);
int			ft_exit(t_ci cmd, t_minish *sh);

/* shared/utils/error.c */
void		ft_error(char *str);
void		env_add_back(t_env **lst, t_env *new);

/* shared/utils/error.c */
void		error(char *str);
t_b			can_add_backtic(char *command);
void		errormsg(char *command, char *text);
char		*joinstrs(char *s1, char *s2);
void		error(char *str);

/* shared/check/check.c */
void		check_usage(int argc, char **argv, t_minish *sh);
void		usage(void);
t_b			can_add_opt(char *args);

/* shared/utils/init.c */
void		init(t_minish *sh, char **argv);
void		init_tcsb(t_csb *cmds);
void		init_twsb(t_wsb *wsb);
void		init_twi(t_wi *i);

/* shared/utils/word_ops.c */
void		ft_wunshift(t_wsb *stack, t_wi info);
void		ft_wpush(t_wsb *stack, t_wi info);
t_wi		ft_wpop(t_wsb *stack);
t_wi		ft_wshift(t_wsb *stack);
t_wsb		duplicate_wsb(t_wsb *stack);

/* shared/utils/read */
void		parse(t_minish *sh);
void		read_line(t_minish *sh);

/* shared/utils/utils */
int			ft_strcmp(char *s1, char *s2);
char		*str_joinsh(char **arg_or_opt, char *str);
t_b			is_sep_type(t_wt wt);
char		*char_of_sep(t_wt wt);
t_wt		is_sep(char s1);

/* shared/utils/handling */
void		handler(t_minish *sh);
void		interactive(t_minish *sh);
void		non_interactive(t_minish *sh);

/* process/signals/signals.c */
void		sigreset(int sig, siginfo_t *info, void *context);
void		interactive_mode_sig(void);
void		ignore_sigquit(void);
int			remove_echoback(t_b echo_ctl_chr);

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
void		end_token_delimiter(char *str, t_lex *lex, t_wi *last);
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
char		*ft_strjoinsh(char *s1, char *s2);

/* process/parser/check.c */
t_b			is_wt_between_values(t_wt word_type, t_wt *list);
t_wt		is_which_wt(char *s1);
t_b			can_delimitate(char *s1, t_wt last, size_t *end);
void		inc_lex(char *s1, size_t *end);

/* process/parser/parser.c */
t_b			parser(t_minish *sh);
t_b			is_begin_good(t_w *word, t_kvp *kvp, t_b *can_continue);
t_b			is_end_good(t_w *word, t_kvp *kvp, t_b *can_continue);
t_b			is_between_good(t_w *word, t_kvp *kvp, t_b *can_continue);

/* process/parser/error.c */
void		parser_error(char *str);
void		handle_parser_err(t_w *word, t_b is_curr, t_b is_next, \
			t_b *can_continue);
void		init_twc(t_wtc *twc);
void		init_kvp(t_wtc *curr, t_wtc *next, t_kvp **kvp);

/* process/shared/utils/constants.c */
t_kvp		*get_kv_pairs(void);
t_cn		set_wt_values(t_wt **curr, t_wt **next, t_cn *cn);
t_cn		get_values_of_index(t_wt key, t_kvp *key_values);
void		get_curr_word_type_consts(t_wtc *wtc);
void		get_next_word_type_consts(t_wtc *wtc);

/* process/shared/utils/alloc.c */
t_wt		*alloc(int mem_nbr);
void		*ft_cpywt(t_wt **dst, const void *src, size_t n);
t_wt		*duptwt(const t_wt *s1);

/* process/expansion/expansion.c */
void		expansion(t_minish *sh);
void		expansion_process(char **str, t_env *env_lst);
void		expand_var(char **str, size_t *start, t_env *env_lst);
void		end_of_expansion(char *str, size_t *end);

/* process/expansion/utils.c */
void		replace_str(char **str, char *to_replace_with, t_lex *lex);
t_b			can_apply_expansion(char *str);
size_t		end_length(t_lex *lex, size_t strlen);
char		*retrieve_env(char *str, t_env *env_lst);

/* process/utils/free.c */
void		free_wsb(t_wsb *wsb);
void		free_csb(t_csb *csb);
void		free_all(t_minish *sh, int nbr);
void		free_for_next_run(t_minish *sh, int nbr);
void		free_kvp(t_kvp **kvp);

/* process/command/command.c */
t_b			generate_cmd(t_minish *sh);
void		add_to_chunk(t_wsb *chunk, t_wi wi);
t_b			can_handle_pipe_found(t_csb *list, t_wsb *wsb);
t_b			can_parse_wsb_to_cmd(t_csb *list, t_wsb *wsb);
t_b			can_add_to_cmd(t_w **head, t_ci *ci);

/* process/command/utils.c */
t_b			is_opt_already_exits(t_wsb *wsb, char *opt);
t_b			is_option(char *opt);
char		*add_arg_or_opt(char **arg_or_opt, t_wi wi);
t_b			can_increment_word(t_w **word);
t_b			handle_redirect(t_w **head, int *infile);

/* utils/s_cmd_ops.c */
void		ft_cunshift(t_csb *stack, t_ci info);
void		ft_cpush(t_csb *stack, t_ci info);
t_ci		ft_cpop(t_csb *stack);
t_ci		ft_cshift(t_csb *stack);
t_csb		duplicate_csb(t_csb *stack);

#endif
