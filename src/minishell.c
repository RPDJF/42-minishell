#include "minishell.h"
#include "env/env.h"

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

t_minishell	*init_minishell(int argc, char **argv, char **envp)
{
	static t_minishell	*minishell;

	if (minishell)
		return (minishell);
	else if (!argc || !argv)
		return (0);
	minishell = galloc(sizeof(t_minishell));
	if (!minishell)
		crash_exit();
	minishell->hostname = mini_gethostname();
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->old_envp = envp;
	minishell->mini_envp = init_minienvp(minishell);
	minishell->envp = &var_to_tab;
	return (minishell);
}

t_minishell	*get_minishell(void)
{
	static t_minishell	*minishell;

	if (!minishell)
		minishell = init_minishell(0, 0, 0);
	return (minishell);
}
