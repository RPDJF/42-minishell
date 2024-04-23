#include "env.h"

t_var	*new_var(char *name, char *value, bool is_env, bool is_name_alloc)
{
	t_var	*var;

	var = galloc(sizeof(t_var));
	if (!var)
		crash_exit();
	if (!is_name_alloc)
		var->name = ft_strdup(name);
	else
		var->name = name;
	var->value = value;
	var->is_env = is_env;
	var->prev = 0;
	var->next = 0;
	return (var);
}

t_var	*update_var(t_var *var)
{
	t_var		*duplicate;

	duplicate = get_var(var->name);
	if (duplicate)
	{
		if (duplicate->prev)
			duplicate->prev->next = var;
		if (duplicate->next)
			duplicate->next->prev = var;
		var->prev = duplicate->prev;
		var->next = duplicate->next;
		if (duplicate->is_env)
			var->is_env = true;
		if (get_minishell()->mini_envp == duplicate)
			get_minishell()->mini_envp = var;
		destroy_var(duplicate);
		return (var);
	}
	add_var(var);
	return (var);
}

t_var	*add_var(t_var *var)
{
	t_minishell	*minishell;

	minishell = get_minishell();
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
