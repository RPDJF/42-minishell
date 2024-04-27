#include "signals.h"

static int	close_here_doc_fd(void)
{
	int	status;

	status = 0;
	if (get_minishell()->dup_stdin != STDIN_FILENO)
	{
		close(get_minishell()->dup_stdin);
		get_minishell()->dup_stdin = STDIN_FILENO;
		status = 1;
	}
	if (get_minishell()->here_doc_fd[1])
	{
		close(get_minishell()->here_doc_fd[1]);
		get_minishell()->here_doc_fd[1] = 0;
		status = 1;
	}
	if (get_minishell()->here_doc_fd[0])
	{
		close(get_minishell()->here_doc_fd[0]);
		get_minishell()->here_doc_fd[0] = 0;
		status = 1;
	}
	return (status);
}

static void	update_line(void)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	print_userinfo();
	rl_redisplay();
}

static void	signal_handler(int signum)
{
	get_minishell()->sigint = signum;
	printf("\n");
	if (signum == SIGINT && get_minishell()->is_interactive)
	{
		if (!close_here_doc_fd())
			update_line();
		update_exitcode(130);
	}
}

void	init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
