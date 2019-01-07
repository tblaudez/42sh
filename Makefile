#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/11 11:11:37 by tblaudez          #+#    #+#              #
#    Updated: 2018/12/15 21:34:56 by tblaudez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SRC :=	src/main.c \
		src/term_tools.c \
		src/key_reader.c \
		src/key_function.c \
		src/key_function2.c \
		src/line.c \
		src/history.c \
		src/history2.c \
		src/history3.c \
		src/ft_catchsign.c \
		src/ft_catchsign2.c \
		src/keyhome.c \
		src/lexer.c \
		src/parser.c \
		src/shell_exec.c \
		src/exec_binary.c \
		src/utils.c \
		src/utils2.c \
		src/utils3.c \
		src/ft_expansion.c \
		src/ft_glob_process.c \
		src/ft_glob_recreate.c \
		src/ft_glob_recloop.c \
		src/ft_glob_check_patern.c \
		src/ft_glob_lst.c \
		src/ft_glob_match.c \
		src/ft_glob_utils.c \
		src/ft_glob_utils2.c \
		src/ft_glob_case.c \
		src/builtin_error.c \
		src/builtin_extra.c \
		src/builtin_extra2.c \
		src/builtin_extra3.c \
		src/builtin.c \
		src/quote.c \
		src/quote2.c \
		src/utils_key_fonction.c \
		src/lifetime.c \
		src/key_function_return.c \
		src/key_function_arrow.c \
		src/key_function_alpha.c \
		src/yank.c \
		src/yank2.c \
		src/past.c \
		src/clear_term.c \
		src/autocomplet.c \
		src/autocomplet_comp.c \
		src/autocomplet_comp2.c \
		src/autocomplet_select.c \
		src/autocomplet_select2.c \
		src/heredoc.c \
		src/heredoc2.c \
		src/exit_free.c

OBJ :=  $(subst src/, objects/, $(SRC:.c=.o))
LIBFT := libft/libft.a
CFLAGS := -Wall -Wextra -Werror -I includes/ -I libft/includes/
INCLUDES_FILES := includes/sh42.h includes/lifetime.h libft/includes/libft.h \
libft/includes/ft_fprintf.h libft/includes/get_next_line.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@printf "\n\e[1;35mCréation du binaire\e[0m - %-50s\n" $@
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -l termcap

objects/%.o: src/%.c Makefile $(INCLUDES_FILES)
	@printf "\e[1;31mCréation des .o\e[0m - %-50s\r" $@
	@mkdir -p objects/
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft/

clean:
	@/bin/rm -rf objects/ && \
	make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME) && \
	make -C libft fclean && \
	rm -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re
