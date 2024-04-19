#include "signals.h"

static void	signal_handler(int signum)
{
	char	*tmp;

	if (get_minishell()->is_interactive)
	{
		if (signum == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			tmp = ft_strdup("130");
			if (!tmp)
				crash_exit();
			update_var(new_var("?", tmp, false, false));
		}
	}
}

void	init_signals(void)
{
	signal(SIGINT, signal_handler);
}
