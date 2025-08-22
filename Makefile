# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 14:10:49 by hallison          #+#    #+#              #
#    Updated: 2025/08/22 15:06:56 by hallison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_PATH) -Iinclude

#subject says be sure to compile with lm, but this throws an error when compiling

LIBFT_PATH = lib/libft
LIBFT = $(LIBFT_PATH)/libft.a

#LOGO = lib/minishell_logo.txt
NAME = raytracer
HEADER = raytracer.h

SRC = main.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)
#	@cat $(LOGO)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -rf $(NAME)

asan: fclean
asan: CFLAGS += -fsanitize=address -g
asan: all

gdb: fclean
gdb: CFLAGS += -g -O0
gdb: all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --track-fds=yes  --quiet --suppressions=readline_suppress.supp ./minishell

valchild:
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --track-fds=yes  --trace-children=yes --quiet --suppressions=readline_suppress.supp ./minishell

re: fclean all

.PHONY: all clean fclean re compile asan
