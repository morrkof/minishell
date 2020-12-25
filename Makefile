# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/03 16:22:35 by ppipes            #+#    #+#              #
#*   Updated: 2020/12/25 13:04:40 by miphigen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c parser.c process_var.c execute.c env_unset.c \
export.c free.c builtin.c env_utils.c get_path.c fork.c export_alph_order.c \
parse_line.c hello.c

HEADER = ./minishell.h
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -Llibft -lft
LIBFT = ./libft/libft.a

.PHONY: all clean fclean re empty

all: $(NAME)
$(NAME): $(OBJ) $(HEADER) $(LIBFT)
	gcc $(OBJ) $(LIBFLAGS) $(CFLAGS) -o $(NAME)
%.o: %.c
	gcc $(CFLAGS) -c $<
$(LIBFT): empty
	$(MAKE) -C ./libft
clean:
	$(MAKE) -C ./libft clean
	rm -rf $(OBJ)
fclean: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)
re: fclean all
empty: 
