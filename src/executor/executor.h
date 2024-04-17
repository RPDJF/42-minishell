#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include "../builtin/builtin.h"
# include "../utils/expand_words.h"
# include "../utils/binary_finder.h"
# include "../prompter/here_doc.h"

typedef struct s_executor
{
	bool	has_pipe;
	t_token	*tokens;
	int		original_fd_in;
	int		original_fd_out;
	int		fd_in;
	int		fd_out;
	int		fd_in_pipe;
}	t_executor;

//	executor:	execute a list of tokens inside minishell
void	executor(t_token *tokens);
//	init_child:	init and execute a child from cmd or builtin token
pid_t	init_child(t_executor *executor, t_token *tokens);
//	exec_pipe:	Handles pipe type tokens
int		exec_pipe(t_executor *executor, t_token *tokens);
//	exec_redir:	handles redirections type tokens
int		exec_redir(t_executor *executor, t_token *tokens);
//	get_wexistatus:	get the exit status from a waitpid status
int		get_wexistatus(int status);
//	has_pipe:	check if a token list has a pipe token
bool	has_pipe(t_token *tokens);
//	switch_fd:	switch file descriptors
void	switch_fd(t_executor *executor, t_pipe *pipe);

#endif