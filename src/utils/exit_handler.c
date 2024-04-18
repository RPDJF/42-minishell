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

void	error_cmd(char *path)
{
	int			err;
	struct stat	path_stat;

	err = errno;
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		error_exit((char *[]){APP_NAME, path, 0}, IS_DIR, 126);
	else if (err == EACCES)
		error_exit((char *[]){APP_NAME, path, 0}, strerror(err), 126);
	else if (!ft_strchr(path, '/'))
		error_exit((char *[]){path, 0}, COMMAND_NOT_FOUND, 127);
	else
		error_exit((char *[]){APP_NAME, path, 0}, strerror(err), 127);
}
