/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:09 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/28 19:09:53 by rude-jes         ###   ########.fr       */
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

# define APP_NAME "minishell"
# define VERSION "0.1"

typedef struct s_minishell
{
	char		*hostname;
}				t_minishell;

//	Type enumerators
typedef enum e_token_type
{
	token_cmd,
	token_builtin,
	token_pipe,
	token_stdin,
	token_stdout,
	token_and,
	token_or,
	token_token_group
}				t_token_type;

typedef enum e_builtin_type
{
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_export,
	builtin_unset,
	builtin_env,
	builtin_exit
}				t_builtin_type;

//	Token structure
typedef struct s_token
{
	void			*data;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

//	Typed token structures
typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	int		argc;
}				t_cmd;

typedef struct s_builtin
{
	t_builtin_type	cmd;
	char			**argv;
	int				argc;
}				t_builtin;

typedef struct s_stdout
{
	bool	isAppend;
	char	*filename;
}				t_stdout;

typedef struct s_stdin
{
	bool	isHeredoc;
	char	*limiter;
	char	*filename;
}				t_stdin;

// EXPORTED FUNCTIONS

//	FROM utils/exit_handler.c

//		crash_exit: exit the program when unexpected error
void		crash_exit(void);

//	FROM utils/init_minishell.c

//		init_minishell: init a new minishell instance
t_minishell	*init_minishell(void);

//	FROM prompt.c

//		prompt: sends a prompt to the user and returns their input as char*
char		*prompt(t_minishell *minishell);

#endif