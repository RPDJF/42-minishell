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
		output = ft_strdup("/bin/minishell");
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
	int		i;

	minishell->mini_envp = 0;
	i = 0;
	while (minishell->old_envp[i])
		i++;
	while (--i >= 0)
	{
		var = new_var(0, 0, 0, true);
		var->name = ft_substr(minishell->old_envp[i], 0,
				ft_strchr(minishell->old_envp[i],
					'=') - minishell->old_envp[i]);
		var->type = var_str;
		if (!var->name)
			crash_exit();
		var->data = parse_var(var->name);
		if (!var->data)
			crash_exit();
		add_var(minishell, var);
	}
	return (minishell->mini_envp);
}
