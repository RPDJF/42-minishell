#include "executor.h"

static size_t	fill_cmd_argv(t_cmd *cmd, t_word **argv, char **cmd_split)
{
	size_t	i;

	i = 0;
	while (cmd_split[i])
	{
		argv[i] = ft_calloc(1, sizeof(t_word));
		if (!argv[i])
			crash_exit();
		argv[i]->str = cmd_split[i];
		i++;
	}
	gfree(cmd_split);
	ft_memmove(argv + i,
		cmd->argv + 1, words_arr_len(cmd->argv) * sizeof(t_word *));
	gfree(cmd->argv);
	return (i);
}

t_word	**parse_cmd_var(t_cmd *cmd)
{
	t_word	**argv;
	char	*cmd_str;
	char	**cmd_split;

	cmd_str = ft_strtrim(cmd->cmd->str, " \t");
	if (!cmd_str)
		crash_exit();
	if (!*cmd_str || *cmd_str != '$')
		return (cmd->argv);
	cmd_str = parse_words(cmd->cmd);
	if (!cmd_str)
		crash_exit();
	cmd_split = ft_split(cmd_str, ' ');
	if (!cmd_split)
		crash_exit();
	gfree(cmd_str);
	argv = galloc((ft_tablen(cmd_split)
				+ words_arr_len(cmd->argv)) * sizeof(t_word *));
	if (!argv)
		crash_exit();
	fill_cmd_argv(cmd, argv, cmd_split);
	cmd->argv = argv;
	cmd->cmd = argv[0];
	cmd->argc = words_arr_len(argv);
	return (argv);
}
