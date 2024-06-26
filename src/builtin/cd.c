/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:00 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 19:24:48 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static bool	check_error(t_cd *cd)
{
	if (cd->argc > 2)
	{
		error_msg((char *[]){APP_NAME, "cd", 0}, "too many arguments");
		return (true);
	}
	if (cd->argc == 1)
	{
		if (get_var("HOME") && get_var("HOME")->value)
			cd->pwd = get_var("HOME")->value;
		else
		{
			error_msg((char *[]){APP_NAME, "cd", 0}, "HOME not set");
			return (true);
		}
		if (!*cd->pwd)
		{
			getcwd(cd->pwd_buff, PATH_MAX);
			cd->pwd = cd->pwd_buff;
		}
	}
	return (false);
}

static int	fn(t_cd *cd)
{
	char	*new_pwd;
	char	*new_oldpwd;

	if (chdir(cd->pwd) == -1)
	{
		error_msg((char *[]){APP_NAME, "cd", cd->pwd, 0}, strerror(errno));
		gfree(cd);
		return (1);
	}
	new_pwd = (char *)addgarbage(getcwd(0, 0));
	if (!new_pwd)
	{
		chdir(cd->oldpwd);
		error_msg((char *[]){APP_NAME, "cd", cd->pwd, 0}, strerror(EACCES));
		gfree(new_pwd);
		gfree(cd);
		return (1);
	}
	new_oldpwd = ft_strdup(cd->oldpwd);
	update_var(new_var("OLDPWD", new_oldpwd, true, false));
	update_var(new_var("PWD", new_pwd, true, false));
	gfree(cd);
	return (0);
}

static t_cd	*init_cd(int argc, char **argv)
{
	t_cd	*cd;

	cd = galloc(sizeof(t_cd));
	cd->argc = argc;
	cd->argv = argv;
	getcwd(cd->oldpwd, PATH_MAX);
	cd->pwd = argv[1];
	cd->exec = &fn;
	if (!check_error(cd))
		return (cd);
	gfree(cd);
	return (0);
}

int	cd(int argc, char **argv)
{
	t_cd	*cd;
	t_var	*var_oldpwd;

	cd = init_cd(argc, argv);
	if (!cd)
		return (1);
	if (!ft_strcmp(cd->pwd, "-"))
	{
		var_oldpwd = get_var("OLDPWD");
		if (!var_oldpwd || !var_oldpwd->value)
		{
			error_msg((char *[]){APP_NAME, "cd", 0}, "OLDPWD not set");
			gfree(cd);
			return (1);
		}
		else if (!*var_oldpwd->value)
		{
			getcwd(cd->pwd_buff, PATH_MAX);
			cd->pwd = cd->pwd_buff;
		}
		else
			cd->pwd = var_oldpwd->value;
	}
	return (cd->exec(cd));
}
