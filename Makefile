# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 14:13:35 by segarcia          #+#    #+#              #
#    Updated: 2022/11/23 14:18:41 by segarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell
SRC			= 	minishell.c			\
				./builtins/pwd.c

OBJS		= $(SRC:.c=.o)

LIBFT		= ./libft/libft.a
LIBFT_PATH	= ./libft
PRINTF		= ./libft/ft_printf/libftprintf.a
PRINTF_PATH	= ./libft/ft_printf

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra
DEBUGFLAG	= -fsanitize=address

all: $(NAME)

$(LIBFT):
	@make bonus -C $(LIBFT_PATH)

$(PRINTF):
	@make -C $(PRINTF_PATH)

$(NAME): $(LIBFT) $(PRINTF) $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(PRINTF) -o $(NAME)

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(PRINTF_PATH)
	@$(RM) *.o

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(PRINTF_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re