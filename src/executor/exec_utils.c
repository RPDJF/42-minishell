#include "executor.h"

bool	is_builtin(t_cmd *cmd)
{
	bool	output;
	char	*cmd_str;

	cmd_str = parse_words(cmd->cmd);
	if (!ft_strcmp(cmd_str, "cd") || !ft_strcmp(cmd_str, "echo")
		|| !ft_strcmp(cmd_str, "export") || !ft_strcmp(cmd_str, "exit")
		|| !ft_strcmp(cmd_str, "pwd") || !ft_strcmp(cmd_str, "unset")
		|| !ft_strcmp(cmd_str, "env"))
		output = true;
	else
		output = false;
	gfree(cmd_str);
	return (output);
}

t_cmd	*find_cmd(t_cmd *cmd)
{
	char	*cmd_str;

	cmd_str = parse_words(cmd->cmd);
	while (cmd->cmd && cmd->cmd->is_var && !*cmd_str)
	{
		cmd->argv++;
		cmd->argc--;
		cmd->cmd = *cmd->argv;
		gfree(cmd_str);
		if (cmd->cmd)
			cmd_str = parse_words(cmd->cmd);
		else
			cmd_str = 0;
	}
	gfree(cmd_str);
	if (!cmd->cmd)
		return (0);
	return (cmd);
}

void	close_all_fd(t_context *context)
{
	while (context)
	{
		if (context->fd_in != STDIN_FILENO)
			close(context->fd_in);
		if (context->fd_out != STDOUT_FILENO)
			close(context->fd_out);
		context = context->next;
	}
}
