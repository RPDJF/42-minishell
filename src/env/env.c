#include "env.h"
#include "../utils/binary_finder.h"

static int	shlvl_parse(char *shlvl)
{
	int		shlvl_int;
	char	*errmsg;
	char	*tmp;

	shlvl_int = ft_atoi(shlvl) + 1;
	if (shlvl_int < 0)
		shlvl_int = 0;
	if (shlvl_int > 999)
	{
		errmsg = ft_itoa(shlvl_int);
		if (!errmsg)
			crash_exit();
		tmp = errmsg;
		errmsg = ft_strsjoin(3,
				"shell level (", errmsg, ") too high, resetting to 1");
		if (!errmsg)
			crash_exit();
		gfree(tmp);
		error_msg((char *[]){APP_NAME, "warning", 0}, errmsg);
		gfree(errmsg);
		shlvl_int = 1;
	}
	return (shlvl_int);
}

static char	*parse_var(char *var_name)
{
	char	*env;
	char	*output;

	if (!ft_strcmp(var_name, "SHLVL"))
	{
		env = getenv("SHLVL");
		if (!env)
			output = ft_strdup("1");
		else
			output = ft_itoa(shlvl_parse(env));
	}
	else if (!ft_strcmp(var_name, "PWD"))
		output = addgarbage(getcwd(0, 0));
	else if (!ft_strcmp(var_name, "SHELL"))
		output = ft_strdup("/usr/local/bin/minishell");
	else
		output = ft_strdup(getenv(var_name));
	if (!output)
		crash_exit();
	return (output);
}

static void	add_default_vars(void)
{
	t_var	*var;
	char	*value;

	value = ft_itoa(0);
	if (!value)
		crash_exit();
	var = new_var("?", value, false, false);
	add_var(var);
}

t_var	*new_env_var(char *env)
{
	t_var	*var;
	char	*name;
	char	*value;

	name = ft_substr(env, 0, ft_strchr(env, '=') - env);
	if (!name)
		crash_exit();
	value = parse_var(name);
	if (!value)
		crash_exit();
	var = new_var(name, value, true, false);
	return (var);
}

t_var	*init_minienvp(void)
{
	t_minishell	*minishell;
	int			i;

	minishell = get_minishell();
	minishell->mini_envp = 0;
	i = 0;
	while (minishell->old_envp[i])
		i++;
	while (--i >= 0)
		add_var(new_env_var(minishell->old_envp[i]));
	add_default_vars();
	return (minishell->mini_envp);
}
