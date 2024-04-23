#include "minishell.h"
#include "env/env.h"
#include "prompter/prompt.h"
#include "signals/signals.h"

static char	*mini_gethostname(void)
{
	const char	hostname[] = "/etc/hostname";
	char		*output;
	char		*tmp;
	char		*line;
	int			fd;

	fd = open(hostname, O_RDONLY);
	if (fd < 0)
		return (0);
	line = ft_get_next_line(fd);
	output = ft_strdup("");
	while (line)
	{
		if (output)
			tmp = output;
		output = ft_strjoin(output, line);
		if (!output)
			return (0);
		if (tmp)
			gfree(tmp);
		gfree(line);
		line = ft_get_next_line(fd);
	}
	output[ft_strlen(output) - 1] = 0;
	return (output);
}

//	TODO: remove debug mode when done

static void	script_mode(void)
{
	t_minishell	*minishell;
	struct stat	buf;

	minishell = get_minishell();
	if (minishell->argc <= 1 || !ft_strcmp(minishell->argv[1], "debug"))
		return ;
	if (!stat(minishell->argv[1], &buf) && !S_ISDIR(buf.st_mode)
		&& !access(minishell->argv[1], R_OK))
	{
		dup2(open(minishell->argv[1], O_RDONLY), STDIN_FILENO);
		minishell->is_script = true;
	}
	else
		error_cmd(minishell->argv[1], true);
}

t_minishell	*init_minishell(int argc, char **argv, char **envp)
{
	static t_minishell	*minishell;

	if (minishell)
		return (minishell);
	else if (!argc || !argv)
		return (0);
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		crash_exit();
	minishell->hostname = mini_gethostname();
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->old_envp = envp;
	minishell->mini_envp = init_minienvp();
	minishell->envp = &var_to_tab;
	minishell->is_interactive = true;
	ms_load_history();
	init_signals();
	script_mode();
	return (minishell);
}

t_minishell	*get_minishell(void)
{
	static t_minishell	*minishell;

	if (!minishell)
		minishell = init_minishell(0, 0, 0);
	return (minishell);
}
