#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/betterft/betterft.h"
# include "utils/exit_handler.h"

# define APP_NAME "minishell"
# define VERSION "0.1"

// Lexer struct
typedef struct s_word
{
	char			*str;
	bool			is_var;
	struct s_word	*next;
}	t_word;

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

//	Token structure
typedef struct s_token
{
	void			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

//	Typed token structures
typedef struct s_cmd
{
	t_word	*cmd;
	t_word	**argv;
	int		argc;
	pid_t	pid;
}				t_cmd;

typedef struct s_builtin
{
	t_builtin_type	cmd;
	t_word			**argv;
	int				argc;
	pid_t			pid;
	int				status;
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

typedef struct s_pipe
{
	int		pipe[2];
}				t_pipe;

typedef struct s_var
{
	bool			is_env;
	char			*name;
	char			*value;
	struct s_var	*prev;
	struct s_var	*next;
}				t_var;

//	Minishell structure
typedef struct s_minishell	t_minishell;
typedef struct s_minishell
{
	int			argc;
	char		**argv;
	char		**old_envp;
	char		**(*envp)(void);
	t_var		*mini_envp;
	char		*hostname;
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
