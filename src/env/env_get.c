#include "env.h"

t_var	*get_var(t_minishell *minishell, char *name)
{
	t_var	*var;

	var = minishell->mini_envp;
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			return (var);
		var = var->next;
	}
	return (0);
}
