/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:42:44 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/29 19:10:03 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

//	Macros
//		Colors definition
# define C_RED "\033[0;31m"
# define C_GREEN "\033[0;32m"
# define C_YELLOW "\033[0;33m"
# define C_BLUE "\033[0;34m"
# define C_MAGENTA "\033[0;35m"
# define C_CYAN "\001\033\[36m\002"
# define C_BLACK "\033[30m"
# define C_WHITE "\033[37m"
# define C_RESET "\001\033\[0m\002"

//	Text effects definition
# define C_BOLD "\033[1m"
# define C_UNDERLINE "\033[4m"
# define C_BLINK "\033[5m"
# define C_REVERSE "\033[7m"
# define C_INVISIBLE "\033[8m"
# define C_STRIKETHROUGH "\033[9m"
# define C_CLEAR "\033[2J\033[1;1H"

//	Background colors definition
# define C_BBLACK "\033[40m"
# define C_BWHITE "\033[47m"
# define C_BRED "\033[41m"
# define C_BGREEN "\033[42m"
# define C_BYELLOW "\033[43m"
# define C_BBLUE "\033[44m"
# define C_BMAGENTA "\001\033[45m\002"
# define C_BCYAN "\033[46m"

#endif