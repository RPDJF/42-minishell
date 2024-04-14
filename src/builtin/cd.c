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
		cd->path = argv[1];
	else
		cd->path = getenv("HOME");
	cd->exec = &chdir;
	if (argc > 2)
	{
		cd->context = get_context(argv, 0);
		error_msg(cd->context, "too many arguments");
		return (0);
	}
	return (cd);
}

int	cd(int argc, char **argv)
{
	t_cd	*cd;

	cd = init_cd(argc, argv);
	if (!cd)
	{
		ft_free_tab(cd->context);
		gfree(cd);
		return (1);
	}
	cd->status = cd->exec(cd->path);
	if (cd->status)
	{
		cd->context = get_context(argv, cd->path);
		error_msg(cd->context, strerror(errno));
		ft_free_tab(cd->context);
		gfree(cd);
		return (1);
	}
	gfree(cd);
	return (0);
}
