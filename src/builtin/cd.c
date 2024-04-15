#include "cd.h"

static char	**get_context(char **argv, char *file)
{
	static char	**context;

	if (context)
		return (context);
	if (!file)
		context = galloc(sizeof(char *) * 2);
	else
		context = galloc(sizeof(char *) * 3);
	if (!context)
		crash_exit();
	context[0] = ft_strdup(ft_strrchr(argv[0], '/') + 1);
	if (!context[0])
		crash_exit();
	if (!file)
		context[1] = 0;
	else
	{
		context[1] = ft_strdup(file);
		context[2] = 0;
	}
	return (context);
}

static t_cd	*init_cd(int argc, char **argv)
{
	t_cd	*cd;

	cd = galloc(sizeof(t_cd));
	if (!cd)
		crash_exit();
	cd->argc = argc;
	cd->argv = argv;
	cd->context = 0;
	cd->status = 0;
	if (argc == 2)
		cd->pwd = ft_strdup(argv[1]);
	else
		cd->pwd = get_var_value("HOME");
	if (!cd->pwd)
		crash_exit();
	cd->oldpwd = getcwd(0, 0);
	cd->exec = &chdir;
	if (argc > 2)
	{
		cd->context = get_context(argv, 0);
		error_msg(cd->context, "too many arguments");
		return (0);
	}
	return (cd);
}

static bool	check_errors(t_cd *cd)
{
	if (!cd->pwd)
	{
		cd->context = get_context(cd->argv, 0);
		error_msg(cd->context, "HOME not set");
		ft_free_tab(cd->context);
		return (true);
	}
	return (false);
}

static void	update_pwd(t_cd *cd)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		crash_exit();
	oldpwd = ft_strdup(cd->oldpwd);
	if (!oldpwd)
		crash_exit();
	update_var(new_var(ft_strdup("PWD"), pwd, var_str, true));
	update_var(new_var(ft_strdup("OLDPWD"), oldpwd, var_str, true));
}

int	cd(int argc, char **argv)
{
	t_cd	*cd;

	cd = init_cd(argc, argv);
	if (!cd || check_errors(cd))
	{
		if (cd)
			gfree(cd);
		return (1);
	}
	cd->status = cd->exec(cd->pwd);
	if (cd->status)
	{
		cd->context = get_context(argv, cd->pwd);
		error_msg(cd->context, strerror(errno));
		ft_free_tab(cd->context);
		gfree(cd->pwd);
		gfree(cd->oldpwd);
		gfree(cd);
		return (1);
	}
	update_pwd(cd);
	gfree(cd->pwd);
	gfree(cd->oldpwd);
	gfree(cd);
	return (0);
}
