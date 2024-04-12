/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:42:44 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/30 01:07:08 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

# ifdef __APPLE__
#  define ENDLINE "$ "
# else
#  define ENDLINE "❥ "
# endif

//	macros
//		Colors definition
# define C_RED "\001\033\[0;31m\002"
# define C_GREEN "\001\033\[0;32m\002"
# define C_YELLOW "\001\033\[0;33m\002"
# define C_BLUE "\001\033\[0;34m\002"
# define C_MAGENTA "\001\033\[0;35m\002"
# define C_CYAN "\001\033\[36m\002"
# define C_BLACK "\001\033\[30m\002"
# define C_WHITE "\001\033\[37m\002"
# define C_RESET "\001\033\[0m\002"

//	Text effects definition
# define C_BOLD "\001\033\[1m\002"
# define C_UNDERLINE "\001\033\[4m\002"
# define C_BLINK "\001\033\[5m\002"
# define C_REVERSE "\001\033\[7m\002"
# define C_INVISIBLE "\001\033\[8m\002"
# define C_STRIKETHROUGH "\001\033\[9m\002"
# define C_CLEAR "\001\033\[2J\001\033\[1;1H"

//	Background colors definition
# define C_BBLACK "\001\033\[40m\002"
# define C_BWHITE "\001\033\[47m\002"
# define C_BRED "\001\033\[41m\002"
# define C_BGREEN "\001\033\[42m\002"
# define C_BYELLOW "\001\033\[43m\002"
# define C_BBLUE "\001\033\[44m\002"
# define C_BMAGENTA "\001\033\[45m\002"
# define C_BCYAN "\001\033\[46m\002"

// Functions
//	prompt: sends a prompt to the user and returns their input as char*
char	*prompt(t_minishell *minishell);

#endif