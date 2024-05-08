/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:04 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:25:05 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		errmsg = ft_arrjoin((char *[]){"shell level (", errmsg,
				") too high, resetting to 1", 0});
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
	char	*output;

	if (!ft_strcmp(var_name, "SHLVL"))
	{
		if (!getenv("SHLVL"))
			output = ft_strdup("1");
		else
			output = ft_itoa(shlvl_parse(getenv("SHLVL")));
	}
	else if (!ft_strcmp(var_name, "PWD"))
		output = addgarbage(getcwd(0, 0));
	else if (!ft_strcmp(var_name, "SHELL"))
	{
		if (!getenv("SHELL"))
			output = ft_strdup("/usr/local/bin/minishell");
		else
			output = ft_strdup(getenv("SHELL"));
	}
	else
		output = ft_strdup(getenv(var_name));
	if (!output)
		crash_exit();
	return (output);
}

static void	add_default_vars(void)
{
	char	*value;

	update_exitcode(0);
	value = ft_itoa(1);
	if (!value)
		crash_exit();
	if (!get_var("SHLVL"))
		add_var(new_var("SHLVL", value, true, false));
	if (!get_var("PWD"))
		add_var(new_var("PWD", parse_var("PWD"), true, false));
	if (!get_var("OLDPWD"))
		add_var(new_var("OLDPWD", 0, true, false));
	if (!get_var("SHELL"))
		add_var(new_var("SHELL", parse_var("SHELL"), false, false));
	value = ft_strdup(APP_NAME);
	if (!value)
		crash_exit();
	if (!get_var("_"))
		add_var(new_var("_", value, true, false));
	value = ft_strdup(DEFAULT_PATH);
	if (!value)
		crash_exit();
	if (!get_var("PATH"))
		add_var(new_var("PATH", value, false, false));
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
