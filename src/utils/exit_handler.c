#include "exit_handler.h"

void	crash_exit(void)
{
	ft_putstr_fd(APP_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);
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
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);
}

void	error_exit(char **context, char *msg, int exitcode)
{
	error_msg(context, msg);
	exit(exitcode);
}
