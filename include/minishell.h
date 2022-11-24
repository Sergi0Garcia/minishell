/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:16:33 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/24 10:12:03 by segarcia         ###   ########.fr       */
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

typedef struct s_info
{
    char sep;
    char *line;
} t_si;

typedef struct s_stack
{
    t_si i;
    struct s_stack *next;
    struct s_stack *prev;
} t_st;

typedef struct s_stack_bundle
{
    int size;
    struct s_stack *head;
    struct s_stack *tail;
} t_sb;

typedef struct s_minishell
{
    t_st st;
    char **env;
    char **argv;
    char *pid;
} t_minish;

int	    ft_pwd(void);
char	**set_env(char **envp);

/* zxterns/utils/error.c */
void ft_error(char *str);

/* externs/utils/init.c */
void    init(t_minish *sh, char **argv, char **env);

/* externs/utils/ops.c */
void ft_unshift(t_sb *stack, t_si info);
void ft_push(t_sb *stack, t_si info);
t_si ft_pop(t_sb *stack);
t_si ft_shift(t_sb *stack);

#endif