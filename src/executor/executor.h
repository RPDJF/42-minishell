#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include "../builtin/builtin.h"
# include "../utils/expand_words.h"
# include "../utils/binary_finder.h"

typedef struct s_executor
{
	bool	has_pipe;
	int		fd_in;
	int		fd_out;
	int		fd_in_pipe;
}	t_executor;

//	executor:	execute a list of tokens inside minishell
void	executor(t_token *tokens);
//	exec_pipe:	Handles pipe type tokens
int		exec_pipe(t_executor *executor, t_token *tokens);
//	exec_redir:	handles redirections type tokens
int		exec_redir(t_executor *executor, t_token *tokens);
//	has_pipe:	check if a token list has a pipe token
bool	has_pipe(t_token *tokens);

#endif