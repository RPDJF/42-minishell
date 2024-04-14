#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include "../builtin/builtin.h"

//	executor: execute a list of tokens inside minishell
void	executor(t_minishell *minishell, t_token *tokens);

#endif