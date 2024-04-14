/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:09 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/14 01:41:20 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/betterft/betterft.h"
# include "utils/exit_handler.h"

# define APP_NAME "minishell"
# define VERSION "0.1"

//	Type enumerators
typedef enum e_token_type
{
	token_cmd,
	token_builtin,
	token_var,
	token_pipe,
	token_stdin,
	token_stdout,
	token_and,
	token_or,
	token_grp
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

typedef enum e_var_type
{
	var_str,
	var_token
}				t_var_type;

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
	pid_t	pid;
}				t_cmd;

typedef struct s_builtin
{
	t_builtin_type	cmd;
	char			**argv;
	int				argc;
	pid_t			pid;
}				t_builtin;

typedef struct s_stdout
{
	bool	is_append;
	char	*filename;
}				t_stdout;

typedef struct s_stdin
{
	bool	is_heredoc;
	char	*limiter;
	char	*filename;
}				t_stdin;

typedef struct s_var
{
	bool			is_env;
	char			*name;
	void			*data;
	t_var_type		type;
	struct s_var	*prev;
	struct s_var	*next;
}				t_var;

//	Minishell structure
typedef struct s_minishell
{
	int			argc;
	char		**argv;
	char		**envp;
	t_var		*mini_envp;
	char		*hostname;
}				t_minishell;

// Lexer struct
typedef struct s_word
{
	char			*str;
	bool			is_var;
	struct s_word	*next;
}	t_word;

//	init_minishell: init a new minishell instance
t_minishell	*init_minishell(int argc, char **argv, char **envp);
// Realloc and return a char ** from str and add the char *neww to the end
char		**strr_realloc(char **str, char *neww);

#endif
