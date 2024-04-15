#include "exit_handler.h"
#include "../minishell.h"

void	crash_exit(void)
{
	int errno_tmp;

	errno_tmp = errno;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(errno_tmp);
}

void	error_msg(char **context, char *msg)
{
	ft_putstr_fd(APP_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
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
