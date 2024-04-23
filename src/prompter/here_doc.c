#include "here_doc.h"

static int	handle_sigint(int *pipe_fd)
{
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (-1);
}

char	*prompt_here_doc(char *delimiter)
{
	char	*line;
	char	*msg;

	write (STDOUT_FILENO, "> ", 2);
	line = ft_get_next_line(STDIN_FILENO);
	if (!line)
	{
		write(STDOUT_FILENO, "\n", 1);
		msg = ft_strsjoin(3, "here-document delimited by end-of-file (wanted `",
				delimiter, "')");
		if (!msg)
			crash_exit();
		error_msg((char *[]){APP_NAME, "warning", 0}, msg);
		gfree(msg);
		return (0);
	}
	line[ft_strlen(line) - 1] = 0;
	return (line);
}

int	here_doc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) < 0)
		crash_exit();
	get_minishell()->here_doc_fd[0] = pipe_fd[0];
	get_minishell()->here_doc_fd[1] = pipe_fd[1];
	line = prompt_here_doc(delimiter);
	while (line && ft_strcmp(line, delimiter))
	{
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
		if (get_minishell()->sigint == SIGINT)
			return (handle_sigint(pipe_fd));
		line = prompt_here_doc(delimiter);
	}
	close(pipe_fd[1]);
	get_minishell()->here_doc_fd[0] = 0;
	get_minishell()->here_doc_fd[1] = 0;
	return (pipe_fd[0]);
}
