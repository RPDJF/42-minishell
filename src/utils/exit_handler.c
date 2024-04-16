#include "exit_handler.h"

void	crash_exit(void)
{
	perror(APP_NAME);
	exit(errno);
}

void	error_msg(char **context, char *msg)
{
	while (context && *context)
	{
		ft_putstr_fd(*context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		context++;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	error_exit(char **context, char *msg, int exitcode)
{
	error_msg(context, msg);
	exit(exitcode);
}
