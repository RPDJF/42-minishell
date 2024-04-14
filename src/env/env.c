#include "env.h"
#include "../utils/binary_finder.h"

static void	*parse_var(char *var_name)
{
	char	*env;
	char	*output;

	if (!ft_strcmp(var_name, "SHLVL"))
	{
		env = getenv("SHLVL");
		if (!env)
			output = ft_strdup("1");
		else
			output = ft_itoa(ft_atoi(env) + 1);
	}
	else if (!ft_strcmp(var_name, "PWD"))
		output = addgarbage(getcwd(0, 0));
	else if (!ft_strcmp(var_name, "SHELL"))
		ft_strdup("/bin/minishell");
	else
		output = ft_strdup(getenv(var_name));
	if (!output)
		crash_exit();
	return (output);
}

// TO DO: DETECT IF ENVP VALUE IS TOKEN OR STRING

t_var	*init_minienvp(t_minishell *minishell)
{
	t_var	*var;
	t_var	*head;
	int		i;

	i = 0;
	head = 0;
	while (minishell->envp[i])
		i++;
	while (--i >= 0)
	{
		var = galloc(sizeof(t_var));
		if (!var)
			crash_exit();
		var->prev = 0;
		var->next = 0;
		var->name = ft_substr(minishell->envp[i], 0,
				ft_strchr(minishell->envp[i], '=') - minishell->envp[i]);
		var->type = var_str;
		var->data = parse_var(var->name);
		if (!var->name || !var->data)
			crash_exit();
		add_var(&head, var);
		i++;
	}
	return (head);
}
