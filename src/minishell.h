/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:09 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/04 22:10:20 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/betterft/betterft.h"
# include "utils/exit_handler.h"

# define APP_NAME "minishell"
# define VERSION "0.1"

typedef struct s_minishell
{
	int			argc;
	char		**argv;
	char		**envp;
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

//	init_minishell: init a new minishell instance
t_minishell	*init_minishell(int argc, char **argv, char **envp);
// Realloc and return a char ** from str and add the char *neww to the end
char		**strr_realloc(char **str, char *neww);

#endif
