#include "env.h"

t_var	*update_var(t_minishell *ms, char *name, void *data, t_var_type type)
{
	t_var	*var;
	t_var	*duplicate;

	duplicate = get_var(ms, name);
	if (duplicate)
	{
		gfree(var->data);
		var->data = data;
		var->type = type;
		return (var);
	}
	var = galloc(sizeof(t_var));
	if (!var)
		crash_exit();
	var->name = name;
	var->type = type;
	var->data = data;
	push_var(&ms->mini_envp, var);
	return (var);
}

t_var	*add_var(t_var **head, t_var *var)
{
	t_var	*tmp;

	if (!head)
		return (0);
	if (!*head)
	{
		*head = var;
		return (var);
	}
	var->prev = 0;
	var->next = *head;
	(*head)->prev = var;
	return (var);
}