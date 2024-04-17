#include "exit.h"

static void	fn(char **context, char *errmsg, int exitcode)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (errmsg)
		error_exit(context, errmsg, exitcode % 256);
	else
		exit(exitcode);
}

static t_exit	*init_exit(int argc, char **argv)
{
	t_exit	*exit;

	exit = galloc(sizeof(t_exit));
	if (!exit)
		crash_exit();
	exit->argc = argc;
	exit->argv = argv;
	exit->exec = &fn;
	return (exit);
}

int	exit_ms(int argc, char **argv)
{
	t_exit	*exit;

	exit = init_exit(argc, argv);
	if (argv[1] && ft_strcmp(ft_itoa(ft_atoi(argv[1])), argv[1]))
		exit->exec((char *[]){APP_NAME, "exit", argv[1], 0},
		"numeric argument required", 2);
	if (argc > 2)
		exit->exec((char *[]){APP_NAME, "exit", 0}, "too many arguments", 1);
	exit->exec(0, 0, ft_atoi(argv[1]));
	return (0);
}
