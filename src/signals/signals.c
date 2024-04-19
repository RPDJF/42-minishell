#include "signals.h"

static void	close_here_doc_fd(void)
{
	if (get_minishell()->here_doc_fd[1])
	{
		write(get_minishell()->here_doc_fd[1], "\n", 1);
		close(get_minishell()->here_doc_fd[1]);
		get_minishell()->here_doc_fd[1] = 0;
	}
	if (get_minishell()->here_doc_fd[0])
	{
		close(get_minishell()->here_doc_fd[0]);
		get_minishell()->here_doc_fd[0] = 0;
	}
}

static void	update_line(void)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	signal_handler(int signum)
{
	char	*tmp;

	get_minishell()->sigint = signum;
	if (signum == SIGINT && get_minishell()->is_interactive)
	{
		close_here_doc_fd();
		update_line();
		tmp = ft_strdup("130");
		if (!tmp)
			crash_exit();
		update_var(new_var("?", tmp, false, false));
	}
}

void	init_signals(void)
{
	signal(SIGINT, signal_handler);
}
