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
	new_oldpwd = ft_strdup(cd->oldpwd);
	if (!new_oldpwd)
		crash_exit();
	update_var(new_var("OLDPWD", new_oldpwd, true, false));
	new_pwd = (char *)addgarbage(getcwd(0, 0));
	if (!new_pwd)
		crash_exit();
	update_var(new_var("PWD", new_pwd, true, false));
	gfree(cd);
	return (0);
}

static t_cd	*init_cd(int argc, char **argv)
{
	t_cd	*cd;

	cd = galloc(sizeof(t_cd));
	if (!cd)
		crash_exit();
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

	cd = init_cd(argc, argv);
	if (!cd)
		return (1);
	return (cd->exec(cd));
}
