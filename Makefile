CC = gcc

CFLAGS = -Wall -Werror -Wextra -Ofast

RM = rm -rf

NAME = minishell

LIBFT_PATH = ./better_ft/

LIBFT_LIB = $(LIBFT_PATH:%=%libft.a)

FILES = minishell_main

CFILES = $(FILES:%=%.c)

all : $(NAME)

clean :
	@echo "\n [$(NAME)] - Nettoyage fichier residuels... ♻️ "
	@$(MAKE) -C $(LIBFT_PATH) fclean

fclean : clean
	@echo "\n [$(NAME)] - Supressions du reste... 🗑️"
	@rm -f $(NAME)

re :
	@make fclean
	@make all

debug : $(CFILES) $(LIBFT_LIB) $(MLX)
	@$(CC) $(CFLAGS) $(CFILES) -g3 -fsanitize=address $(LIBFT_LIB) -o $(NAME)
	@echo " \t$(NAME) compiled ✅"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\33[2K"

$(NAME): $(CFILES) $(LIBFT_LIB) $(MLX)
	@$(CC) $(CFLAGS) $(CFILES) $(LIBFT_LIB) -o $(NAME)
	@echo " \t$(NAME) compiled ✅"

$(LIBFT_LIB): $(LIBFT_PATH)Makefile
	@make -C $(LIBFT_PATH) all

.PHONY : clean fclean all debug re
