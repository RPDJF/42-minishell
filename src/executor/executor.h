#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include "../builtin/builtin.h"
# include "../utils/expand_words.h"
# include "../utils/binary_finder.h"
# include "../prompter/here_doc.h"

typedef struct s_context	t_context;
typedef struct s_context
{
	t_context	*next;
	bool		*has_pipe;
	int			*og_fd_in;
	int			*og_fd_out;
	int			fd_in;
	char		*fd_in_path;
	int			fd_out;
	char		*fd_out_path;
}	t_context;

typedef struct s_executor
{
	bool		has_pipe;
	t_token		*tokens;
	int			og_fd_in;
	int			og_fd_out;
	t_context	*context;
}	t_executor;

//	executor:	execute a list of tokens inside minishell
void	executor(t_token *tokens);
//	init_child:	init and execute a child from cmd or builtin token
pid_t	init_child(t_context *context, t_token *tokens);
//	exec_pipe:	Handles pipe type tokens
int		exec_pipe(t_executor *executor, t_token *tokens);
//	exec_redir:	handles redirections type tokens
void	exec_redir(t_executor *executor, t_token *tokens);
//	wait_tokens:	wait for tokens to finish executing
//	returns last process exit code
int		wait_tokens(t_executor *executor);
//	wait_last_token:	wait for the last token to finish executing
int		wait_last_token(t_executor *executor, t_token *tokens);
//	has_pipe:	check if a token list has a pipe token
bool	has_pipe(t_token *tokens);
//	switch_fd:	switch file descriptors
void	switch_fd(t_executor *executor, t_pipe *pipe);
//	dup_fd:	duplicate file descriptors to STDIN_FILENO and STDOUT_FILENO
int		dup_fd(t_context *context);
//	exit_signint:	exit all processes killing them with SIGINT
void	exit_signint(t_executor *executor);
//	exec_var_init:	initialize local variables for execution
void	exec_var_init(t_executor *executor, t_token *tokens);
//	is_builtin:	check if a command is a builtin
bool	is_builtin(t_cmd *cmd);
//	find_cmd:	find a command in the *cmd;
t_cmd	*find_cmd(t_cmd *cmd);
//	close_all_fd:	close all file descriptors in context
void	close_all_fd(t_context *context);
#endif