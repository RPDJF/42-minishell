#include "parsing.h"

t_token_type	define_type(t_word *cmd)
{
	if (!cmd->is_quoted && !cmd->next)
	{
		if (cmd->str[0] == '<' && !cmd->str[1])
			return (token_stdin);
		if (cmd->str[0] == '<' && cmd->str[1] == '<' && !cmd->str[2])
			return (token_stdin);
		if (cmd->str[0] == '>' && !cmd->str[1])
			return (token_stdout);
		if (cmd->str[0] == '>' && cmd->str[1] == '>' && !cmd->str[2])
			return (token_stdout);
	}
	return (0);
}

t_token	*end_newwtk_delem2(t_word *cmd, t_pars *pars, t_token *neww)
{
	if (neww->type == token_stdout && cmd->str[0] == '>'
		&& cmd->str[1] == '>' && !cmd->str[2])
	{
		if (!pars->tmp1->next)
			return (exit_tk((char *[]){APP_NAME, "token", 0}, \
				"syntax error near unexpected token `newwline'"));
		neww->data = (t_stdout *)ft_calloc(1, sizeof(t_stdout));
		if (!neww->data)
			crash_exit();
		((t_stdout *)(neww)->data)->filename = pars->tmp1->next->cmd;
		((t_stdout *)(neww)->data)->is_append = true;
	}
	return (neww);
}

t_token	*end_newwtk_delem(t_word *cmd, t_pars *pars, t_token *neww)
{
	if (neww->type == token_stdin && cmd->str[0] == '<'
		&& !cmd->str[1])
	{
		if (!pars->tmp1->next)
			return (exit_tk((char *[]){APP_NAME, "token", 0}, \
				"syntax error near unexpected token `newwline'"));
		neww->data = (t_stdin *)ft_calloc(1, sizeof(t_stdin));
		if (!neww->data)
			crash_exit();
		((t_stdin *)(neww)->data)->filename = pars->tmp1->next->cmd;
	}
	else if (neww->type == token_stdout && cmd->str[0] == '>' && !cmd->str[1])
	{
		if (!pars->tmp1->next)
			return (exit_tk((char *[]){APP_NAME, "token", 0}, \
				"syntax error near unexpected token `newwline'"));
		neww->data = (t_stdout *)ft_calloc(1, sizeof(t_stdout));
		if (!neww->data)
			crash_exit();
		((t_stdout *)(neww)->data)->filename = pars->tmp1->next->cmd;
	}
	else if (!end_newwtk_delem2(cmd, pars, neww))
		return (exit_tk((char *[]){APP_NAME, "token", 0}, \
				"syntax error near unexpected token `newwline'"));
	return (neww);
}

t_token	*newwtk_delem(t_word *cmd, t_pars *pars)
{
	t_token	*neww;

	neww = ft_calloc(1, sizeof(t_token));
	if (!neww)
		crash_exit();
	neww->type = define_type(cmd);
	if (neww->type == token_stdin && cmd->str[0] == '<'
		&& cmd->str[1] == '<' && !cmd->str[2])
	{
		if (!pars->tmp1->next)
			return (exit_tk((char *[]){APP_NAME, "token", 0}, \
					"syntax error near unexpected token `newwline'"));
		neww->data = (t_stdin *)ft_calloc(1, sizeof(t_stdin));
		if (!neww->data)
			crash_exit();
		((t_stdin *)(neww)->data)->limiter = join_tword(pars->tmp1->next->cmd);
		((t_stdin *)(neww)->data)->is_heredoc = true;
	}
	else if (!end_newwtk_delem(cmd, pars, neww))
		return (exit_tk((char *[]){APP_NAME, "token", 0}, \
				"syntax error near unexpected token `newwline'"));
	pars->tmp1 = pars->tmp1->next->next;
	return (neww);
}

int	tk_cmd(t_token *neww, t_pars *pars)
{
	t_cmd	*data_tmp;

	neww->data = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!neww->data)
		crash_exit();
	data_tmp = neww->data;
	data_tmp->cmd = pars->tmp1->cmd;
	data_tmp->argv = ft_calloc(arg_count(pars->tmp1->next) + 2, sizeof(t_word));
	if (!data_tmp->argv)
		crash_exit();
	data_tmp->argv[0] = pars->tmp1->cmd;
	pars->tmp1 = pars->tmp1->next;
	if (!pars_arg_tk_cmd(neww, data_tmp, pars))
		return (0);
	return (1);
}
