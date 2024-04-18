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
	bool	is_first;

	is_first = true;
	while (context && *context)
	{
		if (is_first)
			ft_putstr_fd(C_RED, STDERR_FILENO);
		ft_putstr_fd(*context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (is_first)
			ft_putstr_fd(C_RESET, STDERR_FILENO);
		is_first = false;
		context++;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	error_exit(char **context, char *msg, int exitcode)
{
	error_msg(context, msg);
	exit(exitcode);
}
