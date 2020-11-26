# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/03 16:22:35 by ppipes            #+#    #+#              #
#*   Updated: 2020/11/24 20:42:28 by miphigen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = minishell.c parser.c parser_process_var.c
HEADER = ./minishell.h
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
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
