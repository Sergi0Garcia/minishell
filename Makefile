# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 14:13:35 by segarcia          #+#    #+#              #
#    Updated: 2023/02/01 04:41:54 by segarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

SRC			= 	minishell.c						\
				./builtins/ft_pwd.c				\
				./builtins/ft_env.c				\
				./builtins/ft_env_utils.c		\
				./builtins/ft_env_utils2.c		\
				./builtins/ft_cd.c    			\
				./builtins/ft_echo.c 			\
				./builtins/ft_cd_utils.c 		\
				./builtins/ft_export.c  		\
				./builtins/ft_unset.c  			\
				./builtins_tests/tester.c		\
				./builtins_tests/playground.c	\
				./builtins_lst_env/add_back.c	\
				./builtins_lst_env/init.c 		\
				./builtins_lst_env/utils.c  	\
				./builtins/ft_utils.c 			\
				./execution/controller.c 		\
				./execution/redirection.c 		\
				./execution/error.c 			\
				./execve/execve.c 				\
				./shared/errors/error.c 		\
				./shared/utils/init.c			\
				./shared/utils/s_word_ops.c		\
				./shared/utils/read.c 			\
				./shared/checks/check.c			\
				./shared/utils/utils.c			\
				./shared/utils/parsing.c		\
				./shared/utils/alloc.c			\
				./shared/utils/free.c			\
				./shared/utils/s_cmd_ops.c		\
				./shared/display/display.c		\
				./process/handler/handler.c 	\
				./process/signals/signals.c		\
				./process/quoting/quoting.c		\
				./process/parser/parser.c		\
				./process/parser/constant.c		\
				./process/parser/check.c		\
				./process/parser/error.c		\
				./process/lexer/lexer.c			\
				./process/lexer/utils.c			\
				./process/expansion/expansion.c \
				./process/expansion/utils.c		\
				./process/command/utils.c		\
				./process/command/command.c

OBJS		= $(SRC:.c=.o)

LIBFT		= ./libft/libft.a
LIBFT_PATH	= ./libft
PRINTF		= ./libft/ft_printf/libftprintf.a
PRINTF_PATH	= ./libft/ft_printf
GNL			= ./gnl/get_next_line.a
GNL_PATH	= ./gnl

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra -g
RL_FLAG		= -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
DEBUGFLAG	= -fsanitize=address
INC			= /include/minishell.h

all: $(NAME)

$(LIBFT):
	@make bonus -C $(LIBFT_PATH)

$(PRINTF):
	@make -C $(PRINTF_PATH)

$(GNL):
	@make -C $(GNL_PATH)

$(NAME): $(LIBFT) $(PRINTF) $(GNL) $(SRC)
	$(CC) $(DEBUGFLAG) ${RL_FLAG} $(CFLAGS) $(SRC) $(LIBFT) $(PRINTF) $(GNL) -o $(NAME)
	# @make del

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

del:
	rm -rf ./minishell.dSYM

re: fclean all

.PHONY: all clean fclean re
