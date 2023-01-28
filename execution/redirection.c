/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:10:03 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/28 02:25:43 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

// int	get_fd(char *path, t_wt key)
// {
//     int fd;

//     fd = -1;
//     if (!path)
//         return (-1);
//     if (key == LESS)
//     {
//         if (access(path, F_OK) == -1)
//             return (-1);
//         if (access(path, R_OK) == -1)
//             return (-1);
//         fd = open(path, O_RDONLY);
//     }
//     else if (key == GREAT)
//         fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
//     else if (key == DGREAT)
//         fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
//     return (fd);
// }
