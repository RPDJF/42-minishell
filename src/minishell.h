/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:28:16 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 21:10:59 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/betterft/betterft.h"
# include "utils/exit_handler.h"

# define APP_NAME "minishell"
# define VERSION "1.0"

// Lexer struct
typedef struct s_word
{
	char			*str;
	bool			is_var;
	bool			is_quoted;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

//	Type enumerators
typedef enum e_token_type
{
	token_cmd,
	token_var,
	token_pipe,
	token_stdin,
	token_stdout,
	token_and,
	token_or,
	token_subshell
}				t_token_type;

//	Token structure
typedef struct s_context	t_context;
typedef struct s_token
{
	void			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
	t_context		*context;
}				t_token;

//	Typed token structures
typedef struct s_cmd
{
	t_word	*cmd;
	t_word	**argv;
	int		argc;
	int		status;
	bool	started;
	pid_t	pid;
}				t_cmd;

typedef struct s_stdout
{
	bool	is_append;
	t_word	*filename;
}				t_stdout;

typedef struct s_stdin
{
	bool	is_heredoc;
	bool	is_quoted;
	char	*limiter;
	t_word	*filename;
}				t_stdin;

typedef struct s_pipe
{
	int		pipe[2];
}				t_pipe;

typedef struct s_var_init
{
	char	*name;
	t_word	*value;
}				t_var_init;

typedef struct s_subshell
{
	t_token	*token;
	int		status;
	bool	started;
	pid_t	pid;
}				t_subshell;

//	Var structure
typedef struct s_var
{
	bool			is_env;
	char			*name;
	char			*value;
	struct s_var	*prev;
	struct s_var	*next;
}				t_var;

//	Minishell structure
typedef struct s_minishell
{
	int		argc;
	char	**argv;
	char	**old_envp;
	char	**(*envp)(void);
	t_var	*mini_envp;
	char	*hostname;
	bool	is_interactive;
	bool	is_script;
	int		sigint;
	int		here_doc_fd[2];
	int		dup_stdin;
	pid_t	cur_pid;
}				t_minishell;

//	init_minishell: init a new minishell instance
t_minishell	*init_minishell(int argc, char **argv, char **envp);
//	get_minishell: get the current minishell instance
//	the instance has to be manually initialized with init_minishell
//	return: t_minishell pointer
t_minishell	*get_minishell(void);
// Realloc and return a char ** from str and add the char *neww to the end
char		**strr_realloc(char **str, char *neww);

#endif
