/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:09 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/27 15:06:23 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/betterft/betterft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_minishell
{
	char		*hostname;
}				t_minishell;

# define VERSION "0.1"

// FROM utils/exit_handler.c

//		crash_exit: exit the program when unexpected error
void		crash_exit(void);

//	FROM utils/init_minishell.c

//		init_minishell: init a new minishell instance
t_minishell	*init_minishell(void);

// FROM prompt.c

//		prompt: sends a prompt to the user and returns their input as char*
char		*prompt(t_minishell *minishell);

#endif