#include "exit.h"

static void	fn(char **context, char *errmsg, int exitcode)
{
	if (errmsg)
		error_exit(context, errmsg, exitcode % 256);
	else
		exit(exitcode);
}

int	exit_ms(int argc, char **argv)
{
	if (argv[1] && ft_strcmp(ft_itoa(ft_atoi(argv[1])), argv[1]))
		fn((char *[]){APP_NAME, "exit", argv[1], 0},
			"numeric argument required", 2);
	if (argc > 2)
		fn((char *[]){APP_NAME, "exit", 0}, "too many arguments", 1);
	if (argv[1])
		fn(0, 0, ft_atoi(argv[1]));
	else
		fn(0, 0, 0);
	return (0);
}
