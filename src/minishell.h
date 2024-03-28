/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:09 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/28 13:48:02 by rude-jes         ###   ########.fr       */
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

typedef enum e_builtin_cmd
{
	type_echo,
	type_cd,
	type_pwd,
	type_export,
	type_unset,
	type_env,
	type_exit
}				t_builtin_cmd;

typedef struct s_error_msg
{
	char	**context;
	char	*msg;
	int		exitcode;
}				t_error_msg;

# define APP_NAME "minishell"
# define VERSION "0.1"

// FROM utils/exit_handler.c

//		crash_exit: exit the program when unexpected error
void		crash_exit(void);
//		error_exit: exit the program when expected error with specific message
void		error_exit(char **context, char *msg, int exitcode);

//	FROM utils/init_minishell.c

//		init_minishell: init a new minishell instance
t_minishell	*init_minishell(void);

// FROM prompt.c

//		prompt: sends a prompt to the user and returns their input as char*
char		*prompt(t_minishell *minishell);

#endif