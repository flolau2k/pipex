# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 11:17:07 by flauer            #+#    #+#              #
#    Updated: 2023/05/26 11:31:09 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex

CC =		cc
#CFLAGS =	-g -Wall -Wextra -Werror
CFLAGS = -g

LIBFT =		libft/libft.a

OBJDIR =	obj/
SRCDIR =	src/

FILES =		pipex.c

SRC =		$(addprefix $(SRCDIR), $(FILES))
OBJ =		$(addprefix $(OBJDIR), $(FILES:%.c=%.o))

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -Llibft -lft
	@echo "built $(NAME)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	make -C libft clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)

re:	fclean all

$(LIBFT):
	@git submodule update --init --recursive --remote
	@make -C $(@D)

.PHONY =	all clean fclean re

obj/printenv.o: src/printenv.c
	$(CC) $(CFLAGS) -c -o $@ $<

printenv: obj/printenv.o
	$(CC) $(CFLAGS) -o printenv obj/printenv.o -Llibft -lft
