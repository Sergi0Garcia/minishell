# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 14:13:35 by segarcia          #+#    #+#              #
#    Updated: 2022/11/27 14:52:46 by segarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell
SRC			= 	minishell.c						\
				./builtins/pwd.c				\
				./builtins/env.c				\
				./builtins/ft_cd.c    			\
				./builtins/echo.c 				\
				./lst_env/add_back.c			\
				./lst_env/init.c 				\
				./lst_env/utils.c  				\
				./externs/utils/error.c 		\
				./externs/utils/init.c			\
				./externs/utils/line_ops.c		\
				./externs/utils/handler.c 		\
				./externs/utils/parsing.c 		\
				./externs/utils/pipe.c 			\
				./externs/utils/redirection.c 	\
				./externs/utils/wildcard.c

OBJS		= $(SRC:.c=.o)

LIBFT		= ./libft/libft.a
LIBFT_PATH	= ./libft
PRINTF		= ./libft/ft_printf/libftprintf.a
PRINTF_PATH	= ./libft/ft_printf
GNL			= ./gnl/get_next_line.a
GNL_PATH	= ./gnl

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra
RL_FLAG		= -lreadline
DEBUGFLAG	= -fsanitize=address

all: $(NAME)

$(LIBFT):
	@make bonus -C $(LIBFT_PATH)

$(PRINTF):
	@make -C $(PRINTF_PATH)

$(GNL):
	@make -C $(GNL_PATH)

$(NAME): $(LIBFT) $(PRINTF) $(GNL) $(SRC)
	$(CC) ${RL_FLAG} $(DEBUGFLAG) $(CFLAGS) $(SRC) $(LIBFT) $(PRINTF) $(GNL) -o $(NAME)

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(PRINTF_PATH)
	@make clean -C $(GNL_PATH)
	@$(RM) *.o

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(PRINTF_PATH)
	@make fclean -C $(GNL_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
