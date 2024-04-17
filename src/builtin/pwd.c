#include "pwd.h"

static t_pwd	*init_pwd(int argc, char **argv)
{
	t_pwd	*pwd;

	pwd = galloc(sizeof(t_pwd));
	if (!pwd)
		crash_exit();
	pwd->argc = argc;
	pwd->argv = argv;
	pwd->exec = &ft_putendl_fd;
	return (pwd);
}

static bool	is_opt(t_pwd *pwd, char *str)
{
	bool	is_option_valid;
	int		i;

	if (*str != '-')
		return (false);
	while (++str, *str)
	{
		is_option_valid = false;
		i = -1;
		while (PWD_OPTIONS[++i])
			if (*str == PWD_OPTIONS[i])
				is_option_valid = true;
		if (!is_option_valid)
			return (false);
	}
	return (true);
}

static void	load_opt(t_pwd *pwd, char *options)
{
	(void)pwd;
	(void)options;
	return ;
}

int	pwd(int argc, char **argv)
{
	t_pwd	*pwd;
	char	*pwd_str;
	int		i;

	pwd = init_pwd(argc, argv);
	i = 0;
	while (argv[++i])
		if (is_opt(pwd, argv[i]))
			load_opt(pwd, argv[i]);
	pwd_str = getcwd(0, 0);
	pwd->exec(pwd_str, STDOUT_FILENO);
	gfree(pwd_str);
	gfree(pwd);
}
