/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:42:44 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/29 22:01:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

# ifndef __APPLE__
//	macros
//		Colors definition
#  define C_RED "\001\033\[0;31m\002"
#  define C_GREEN "\001\033\[0;32m\002"
#  define C_YELLOW "\001\033\[0;33m\002"
#  define C_BLUE "\001\033\[0;34m\002"
#  define C_MAGENTA "\001\033\[0;35m\002"
#  define C_CYAN "\001\033\[36m\002"
#  define C_BLACK "\001\033\[30m\002"
#  define C_WHITE "\001\033\[37m\002"
#  define C_RESET "\001\033\[0m\002"

//	Text effects definition
#  define C_BOLD "\001\033\[1m\002"
#  define C_UNDERLINE "\001\033\[4m\002"
#  define C_BLINK "\001\033\[5m\002"
#  define C_REVERSE "\001\033\[7m\002"
#  define C_INVISIBLE "\001\033\[8m\002"
#  define C_STRIKETHROUGH "\001\033\[9m\002"
#  define C_CLEAR "\001\033\[2J\001\033\[1;1H"

//	Background colors definition
#  define C_BBLACK "\001\033\[40m\002"
#  define C_BWHITE "\001\033\[47m\002"
#  define C_BRED "\001\033\[41m\002"
#  define C_BGREEN "\001\033\[42m\002"
#  define C_BYELLOW "\001\033\[43m\002"
#  define C_BBLUE "\001\033\[44m\002"
#  define C_BMAGENTA "\001\033\[45m\002"
#  define C_BCYAN "\001\033\[46m\002"
# endif

# ifdef __APPLE__
//	colors aren't correctly supported by MacOS realdline
//	macros
//		Colors definition
#  define C_RED ""
#  define C_GREEN ""
#  define C_YELLOW ""
#  define C_BLUE ""
#  define C_MAGENTA ""
#  define C_CYAN ""
#  define C_BLACK ""
#  define C_WHITE ""
#  define C_RESET ""

//	Text effects definition
#  define C_BOLD ""
#  define C_UNDERLINE ""
#  define C_BLINK ""
#  define C_REVERSE ""
#  define C_INVISIBLE ""
#  define C_STRIKETHROUGH ""
#  define C_CLEAR ""

//	Background colors definition
#  define C_BBLACK ""
#  define C_BWHITE ""
#  define C_BRED ""
#  define C_BGREEN ""
#  define C_BYELLOW ""
#  define C_BBLUE ""
#  define C_BMAGENTA ""
#  define C_BCYAN ""
# endif

#endif