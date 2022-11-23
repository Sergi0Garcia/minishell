# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 11:20:39 by segarcia          #+#    #+#              #
#    Updated: 2022/06/09 14:45:10 by segarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	utils/ft_itoa.c 			\
					utils/ft_itoau.c 			\
					printers/ft_printf_char.c	\
					printers/ft_printf_hex.c	\
					printers/ft_printf_int.c	\
					printers/ft_printf_intu.c	\
					printers/ft_printf_ptr.c	\
					printers/ft_printf_str.c	\
					ft_printf.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= libftprintf.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
