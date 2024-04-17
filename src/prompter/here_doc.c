#include "here_doc.h"

static void	write_to_history(bool trigger, char *pipe_content)
{
	if (trigger)
	{
		add_history(pipe_content);
		ms_write_history(pipe_content);
		gfree(pipe_content);
	}
}

static void	fill_pipe_content(bool trigger, char **pipe_content, char *line)
{
	char	*tmp;

	tmp = *pipe_content;
	*pipe_content = ft_strsjoin(3, *pipe_content, "\n", line);
	if (!*pipe_content)
		crash_exit();
	if (trigger)
		gfree(tmp);
}

int	here_doc(char *delimiter)
{
	bool	trigger;
	int		pipe_fd[2];
	char	*pipe_content;
	char	*line;

	trigger = 0;
	pipe_content = "";
	if (pipe(pipe_fd) < 0)
		crash_exit();
	line = readline("> ");
	while (line && ft_strcmp(line, delimiter))
	{
		ft_putendl_fd(line, pipe_fd[1]);
		fill_pipe_content(trigger, &pipe_content, line);
		free(line);
		line = readline("> ");
		trigger = 1;
	}
	close(pipe_fd[1]);
	write_to_history(trigger, pipe_content);
	return (pipe_fd[0]);
}
