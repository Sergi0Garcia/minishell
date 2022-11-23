/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:16:28 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/09 14:36:58 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

char	*ft_itoa(int n);
char	*ft_itoau(int n);
int		ft_printf_char(int c);
int		ft_printf_hex(unsigned int n, char format);
int		ft_printf_int(int n);
int		ft_printf_intu(unsigned int n);
int		ft_printf_ptr(unsigned long long ptr);
int		ft_printf_str(const char *str);
int		ft_printf(const char *str, ...);

#endif
