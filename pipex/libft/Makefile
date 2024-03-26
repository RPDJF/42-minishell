# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 17:53:51 by ilyanar           #+#    #+#              #
#    Updated: 2024/01/22 16:53:36 by ilyanar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

NAME = libft.a


CFILES = $(FILES:%=%.c)

OFILES = $(FILES:%=%.o)

ALLCFILES = $(ALLFILES:%=%.c)

ALLOFILES = $(ALLFILES:%=%.o)

ALLFILES = $(FILES) $(BONUSFILES)



FILES = ft_strlen \
	ft_memmove \
	ft_memcpy \
	ft_strlcpy \
	ft_strlcat \
	ft_isalpha \
	ft_isdigit \
	ft_isalnum \
	ft_isascii \
	ft_isprint \
	ft_memset \
	ft_bzero \
	ft_toupper \
	ft_tolower \
	ft_strchr \
	ft_strrchr \
	ft_strncmp \
	ft_memchr \
	ft_memcmp \
	ft_strnstr \
	ft_atoi \
	ft_calloc \
	ft_strdup \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_split \
	ft_itoa \
	ft_strmapi \
	ft_striteri \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd \
	ft_putnbr_base \
	ft_printf \
	ft_printf_utils \
	ft_rev_tab \
	get_next_line \
	get_next_line_utils \
	ft_printf \
	ft_printf_utils \
	ft_lstnew \
    ft_lstadd_front \
	ft_lstsize \
	ft_lstlast \
	ft_lstadd_back \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap \
	ft_free_tab

all : $(NAME)

%.o : %.c
	@printf "\t⏳Compiling :3 $<...⌛️\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\33[2K"

$(NAME) : $(OFILES)
	@printf "\tcompiling...\r"
	@ar -rc $@ $(OFILES)
	@printf "\33[2K"
	@echo "\t$(NAME) compiled ✅"

clean :
	@echo "\n [$(NAME)] - Nettoyage fichier residuels... ♻️ "
	@$(RM) $(OFILES)

fclean : clean
	@echo "\n [$(NAME)] - supressions du reste... 🗑️"
	@$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean all re
