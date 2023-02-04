/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:41:50 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/04 15:34:03 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int  g_status;

static int str_numeric(char *str)
{
    int len;
    int i;

    len = ft_strlen(str);
    i = 0;
    while (i < len)
    {
        if (str[i] == '-' && str[i + 1] 
            && str[i + 1] >= '0' && str[i + 1] <= '9')
            return (1);
        else if (str[i] == '+' && i == 0)
            i++;
        else if (str[i] == '+' && i > 0)
            return (2);
        else if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (2);
    }
    return (0);
}

int ft_exit(t_ci cmd)
{
    int res;
    char **c_args;

    if (!cmd.opts && !ft_strlen(cmd.opts)
        && !cmd.args && !ft_strlen(cmd.args))
    {
        ft_printf("exit\n");
        exit(0);
    }
    if (cmd.opts && ft_strlen(cmd.opts))
    {
        if (str_numeric(cmd.opts) == 1)
        {
            ft_printf("error\n");
            exit(1);
        }
        ci_error(ERR_NUM_ARG, 255);
        exit(255);
    }
    if (cmd.args && ft_strlen(cmd.args))
    {
        c_args = ft_split(cmd.args, ' ');
        if (c_args && c_child(c_args) > 1)
            return (ci_error(ERR_EXIT_MARG, 1));
        res = str_numeric(c_args[0]);
        if (res == 2)
        {
            ft_printf("exit\n");
            ci_error(ERR_NUM_ARG, 255);
            exit(255);
        }
        if (res == 1)
        {
            ft_printf("exit\n");
            exit(255);
        }
        ft_printf("error\n");
        exit(ft_atoi(c_args[0]) % 256);
    }
    return (0);
}