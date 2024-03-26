# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 12:16:20 by ilyanar           #+#    #+#              #
#    Updated: 2024/02/20 19:32:55 by ilyanar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

NAME = pipex
BONUS_NAME = pipex_bonus

LIBFT_PATH = ./libft/
BONUS_PATH = ./bonus/

LIBFT_LIB = $(LIBFT_PATH:%=%libft.a)

BONUS_FILES = $(BONUS_PATH)pipex_bonus $(BFILES)

CBONUS_FILES = $(BONUS_FILES:%=%.c)

BFILES = pipex \
		pipex_utils \
		pipex_utils2 \
		pipex_utils3 \
		pipex_utils4

FILES = pipex \
		pipex_utils \
		pipex_utils2 \
		pipex_utils3 \
		pipex_utils4 \
		pipex_main

CFILES = $(FILES:%=%.c)

all : $(NAME)

clean :
	@echo "\n [$(NAME)] - Nettoyage fichier residuels... ♻️ "
	@$(MAKE) -C $(LIBFT_PATH) fclean

fclean : clean
	@echo "\n [$(NAME)] - Supressions du reste... 🗑️"
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)

re : fclean all

bonus: $(BONUS_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\33[2K"

$(NAME): $(CFILES) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(CFILES) $(LIBFT_LIB) -o $(NAME)
	@echo " \t$(NAME) compiled ✅"

$(LIBFT_LIB): $(LIBFT_PATH)Makefile
	@make -C $(LIBFT_PATH) all

$(BONUS_NAME): $(CBONUS_FILES) $(LIBFT_LIB)
	@printf "\t⏳Compiling bonus :3 $<...⌛️\r"
	@$(CC) $(CFLAGS) $(CBONUS_FILES) $(LIBFT_LIB) -o pipex
	@printf "\33[2K"
	@echo "\tpipex with bonus compiled ✅"

.PHONY : clean fclean all re
