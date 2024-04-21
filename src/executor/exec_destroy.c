#include "executor.h"

static void	destroy_words(t_word *word)
{
	t_word	*next;

	while (word)
	{
		next = word->next;
		gfree(word->str);
		gfree(word);
		word = next;
	}
}

static void	destroy_redirtokens(t_token *token)
{
	if (token->type == token_stdout)
	{
		gfree(((t_stdout *)token->data)->filename);
		gfree(token->data);
	}
	else if (token->type == token_stdin)
	{
		if (((t_stdin *)token->data)->filename)
			gfree(((t_stdin *)token->data)->filename);
		if (((t_stdin *)token->data)->limiter)
			gfree(((t_stdin *)token->data)->limiter);
		gfree(token->data);
	}
}

static void	destroy_cmdtoken(t_token *token)
{
	t_cmd	*cmd;
	t_word	**argv;

	cmd = (t_cmd *)token->data;
	destroy_words(cmd->cmd);
	argv = cmd->argv;
	while (++argv, *argv)
		destroy_words(*argv);
	gfree(cmd->argv);
	gfree(cmd);
}

static void	destroy_tokens(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->type == token_cmd)
			destroy_cmdtoken(token);
		else if (token->type == token_stdout || token->type == token_stdin)
			destroy_redirtokens(token);
		else if (token->type == token_var)
		{
			gfree(((t_var_init *)token->data)->name);
			destroy_words(((t_var_init *)token->data)->value);
			gfree(token->data);
		}
		gfree(token);
		token = next;
	}
}

void	exec_destroy(t_executor *exec)
{
	t_context	*context;
	t_context	*next;

	context = exec->context;
	while (context)
	{
		next = context->next;
		gfree(context);
		context = next;
	}
	destroy_tokens(exec->tokens);
	gfree(exec);
}