/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:55:06 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/23 14:34:03 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
int		get_nl_idx(char *ptr);
char	*ft_strjoin(char *s1, char *s2);
void	cpystr_increment(char *s1, char *s2, size_t *num);

#endif