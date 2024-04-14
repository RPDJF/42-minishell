#include "env.h"

t_var	*new_var(char *name, void *data, t_var_type type, bool is_env)
{
	t_var	*var;

	var = galloc(sizeof(t_var));
	if (!var)
		crash_exit();
	var->name = name;
	var->data = data;
	var->type = type;
	var->is_env = is_env;
	var->prev = 0;
	var->next = 0;
	return (var);
}

t_var	*update_var(t_minishell *minishell, t_var *var)
{
	t_var	*duplicate;

	duplicate = get_var(minishell, var->name);
	if (duplicate)
	{
		duplicate->data = var->data;
		duplicate->type = var->type;
		duplicate->is_env = var->is_env;
		destroy_var(var);
		return (duplicate);
	}
	var = galloc(sizeof(t_var));
	if (!var)
		crash_exit();
	add_var(minishell, var);
	return (var);
}

t_var	*add_var(t_minishell *minishell, t_var *var)
{
	var->prev = 0;
	var->next = minishell->mini_envp;
	if (!minishell->mini_envp)
	{
		minishell->mini_envp = var;
		return (var);
	}
	minishell->mini_envp->prev = var;
	minishell->mini_envp = var;
	return (var);
}
