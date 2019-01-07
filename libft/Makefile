# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 15:48:20 by tblaudez          #+#    #+#              #
#    Updated: 2018/12/12 19:21:29 by tblaudez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= libft.a
SRC:= src/ft_atoi.c src/ft_strncat.c src/ft_bzero.c \
src/ft_strncmp.c src/ft_isalnum.c src/ft_memset.c src/ft_strncpy.c \
src/ft_isalpha.c src/ft_strcat.c src/ft_strnstr.c src/ft_isascii.c \
src/ft_strchr.c src/ft_strrchr.c src/ft_isdigit.c src/ft_strcmp.c src/ft_strstr.c \
src/ft_isprint.c src/ft_strcpy.c src/ft_strdup.c src/ft_memmove.c \
src/ft_strlcat.c src/ft_memcmp.c src/ft_strlen.c src/ft_memalloc.c \
src/ft_memdel.c src/ft_strnew.c src/ft_strdel.c src/ft_strequ.c \
src/ft_strnequ.c src/ft_strsub.c src/ft_strsplit.c src/ft_itoa.c src/ft_putchar.c \
src/ft_putstr.c src/ft_putendl.c src/ft_putchar_fd.c src/ft_putstr_fd.c \
src/ft_putendl_fd.c src/ft_isspace.c src/ft_str_is.c \
src/ft_islower.c src/ft_isupper.c src/ft_strndup.c src/ft_charsrc.c src/ft_nbrdig.c \
src/ft_atoibase.c src/ft_strreplace.c src/ft_power.c src/ft_strjoinfree.c \
src/ft_itoabase.c src/ft_strtrim.c src/get_next_line.c src/ft_fprintf/ft_fprintf.c \
src/ft_fprintf/apply_flags.c src/ft_fprintf/get_alpha.c src/ft_fprintf/get_numeric.c \
src/ft_fprintf/utils.c src/ft_fprintf/custom_func.c src/ft_strarraydel.c
OBJ:= $(subst src/, objects/, $(SRC:.c=.o))
CFLAGS:= -Wall -Wextra -Werror -I includes/ -I ../includes/

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\n\e[1;33mCréation du binaire \e[0m- %s\n" $(NAME)
	@ar rc $(NAME) $(OBJ) \
	&& ranlib $(NAME)

objects/%.o: src/%.c Makefile
	@printf "\e[1;32mCréation des .o \e[0m- %-50s\r" $@
	@mkdir -p objects/ft_fprintf
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -rf objects/

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
