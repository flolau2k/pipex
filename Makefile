# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 11:17:07 by flauer            #+#    #+#              #
#    Updated: 2023/06/23 15:17:37 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex

CC =		cc
CFLAGS =	-g -Wall -Wextra -Werror

LIBFT =		libft/libft.a

OBJDIR =	obj
SRCDIR =	src
BONUSDIR =	bonus
OBJDIR_B =	obj_bonus
TEST_DIR = 	test

FILES =		pipex.c utils.c
F_BONUS =	pipex_bonus.c utils_bonus.c here_doc_bonus.c errors.c file_utils.c \
			pipe_functions.c
TEST_F = 	pipex_tester.c

SRC =		$(addprefix $(SRCDIR)/, $(FILES))
OBJ =		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
SRC_BONUS =	$(addprefix $(BONUSDIR)/, $(F_BONUS))
OBJ_BONUS = $(addprefix $(OBJDIR_B)/, $(F_BONUS:%.c=%.o))
TEST_SRC = 	$(addprefix $(TEST_DIR)/, $(TEST_F))
TEST_OBJ = 	$(addprefix $(TEST_DIR)/, $(TEST_F:%.c=%.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -Llibft -lft
	@echo "built $(NAME)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	make -C libft clean
	/bin/rm -rf $(OBJDIR)
	/bin/rm -rf $(OBJDIR_B)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)

re:	fclean all

bonus: $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) -Llibft -lft
	@echo "built $(NAME) bonus"

$(OBJDIR_B)/%.o: $(BONUSDIR)/%.c | $(OBJDIR_B)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR_B):
	@mkdir -p $(OBJDIR_B)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TEST_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o pipex_tests $(TEST_OBJ) -Llibft -lft
	@echo "built tests"

$(LIBFT):
	@git submodule update --init --recursive --remote
	@make -C $(@D)

.PHONY =	all clean fclean re bonus
