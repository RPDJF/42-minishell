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

static void	add_default_vars(void)
{
	t_var	*var;
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = ft_strdup("?");
	if (!tmp_name)
		crash_exit();
	tmp_value = ft_itoa(0);
	if (!tmp_value)
		crash_exit();
	var = new_var(tmp_name, tmp_value, false);
	add_var(var);
}

t_var	*init_minienvp(void)
{
	t_minishell	*minishell;
	t_var		*var;
	int			i;

	minishell = get_minishell();
	minishell->mini_envp = 0;
	i = 0;
	while (minishell->old_envp[i])
		i++;
	while (--i >= 0)
	{
		var = new_var(0, 0, true);
		var->name = ft_substr(minishell->old_envp[i], 0,
				ft_strchr(minishell->old_envp[i],
					'=') - minishell->old_envp[i]);
		if (!var->name)
			crash_exit();
		var->value = parse_var(var->name);
		if (!var->value)
			crash_exit();
		add_var(var);
	}
	add_default_vars();
	return (minishell->mini_envp);
}
