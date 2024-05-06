#include "history.h"

static char	*get_history_filename(void)
{
	char	*filename;
	char	*home;

	home = get_var_value("HOME");
	if (!*home || !ft_strchr(home, '/'))
	{
		gfree(home);
		return (0);
	}
	if (*(ft_strrchr(home, '/') + 1))
		filename = ft_arrjoin((char *[]){home, "/", MINISHELL_HISTORY, 0});
	else
		filename = ft_strjoin(home, MINISHELL_HISTORY);
	if (!filename)
		crash_exit();
	gfree(home);
	return (filename);
}

int	ms_write_history(char *input)
{
	int		history_fd;
	char	*filename;

	filename = get_history_filename();
	if (!filename)
	{
		gfree(filename);
		return (-1);
	}
	history_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0600);
	if (history_fd < 0)
	{
		gfree(filename);
		return (history_fd);
	}
	write(history_fd, input, ft_strlen(input));
	write(history_fd, "\n", 1);
	close(history_fd);
	gfree(filename);
	return (0);
}

int	ms_load_history(void)
{
	int		history_fd;
	char	*filename;
	char	*line;

	filename = get_history_filename();
	if (!filename)
		gfree(filename);
	if (!filename)
		return (-1);
	history_fd = open(filename, O_RDONLY);
	if (history_fd < 0)
		gfree(filename);
	if (history_fd < 0)
		return (history_fd);
	line = ft_get_next_line(history_fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		add_history(line);
		gfree(line);
		line = ft_get_next_line(history_fd);
	}
	close(history_fd);
	gfree(filename);
	return (0);
}
