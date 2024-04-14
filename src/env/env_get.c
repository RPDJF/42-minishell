#include "env.h"

t_var	*get_var(char *name)
{
	t_minishell	*minishell;
	t_var		*var;

	minishell = get_minishell();
	var = minishell->mini_envp;
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			return (var);
		var = var->next;
	}
	return (0);
}

char	*get_envp_value(char *name, char **envp)
{
	int		i;
	char	*value;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
		{
			value = ft_strchr(envp[i], '=') + 1;
			return (value);
		}
		i++;
	}
	return (0);
}
