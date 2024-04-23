#include "executor.h"

static bool	has_command(t_token *tokens)
{
	while (tokens && tokens->type != token_pipe)
	{
		if (tokens->type == token_cmd)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

void	exec_var_init(t_executor *executor, t_token *token)
{
	t_var_init	*var_init;
	t_var		*var;

	if (has_command(token) || executor->has_pipe)
		return ;
	var_init = (t_var_init *)token->data;
	var = new_var(var_init->name,
			parse_words(var_init->value), false, false);
	update_var(var);
}
