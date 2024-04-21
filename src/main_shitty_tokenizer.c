#include "minishell.h"
#include "prompter/prompt.h"
#include "parsing/parsing.h"
#include "lexer/lexer.h"
#include "utils/exit_handler.h"
#include "executor/executor.h"

static t_token	*shitty_quick_tokenizer(t_tlex *lexer)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*tokens;
	int	i;

	if (!lexer || !lexer->cmd)
		return (0);
	tmp = 0;
	tokens = 0;
	i = -1;
	while (++i, lexer)
	{
		if (tokens)
		{
			tmp = tokens;
			tokens = tokens->next;
		}
		if (!ft_strcmp(lexer->cmd->str, "<<"))
		{
			tokens = galloc(sizeof(t_token));
			if (tmp)
				tmp->next = tokens;
			if (i == 0)
				head = tokens;
			tokens->type = token_stdin;
			tokens->data = ft_calloc(1, sizeof(t_stdin));
			((t_stdin *)tokens->data)->is_heredoc = true;
			lexer = lexer->next;
			((t_stdin *)tokens->data)->limiter = ft_strdup(lexer->cmd->str);
			tokens->next = 0;
		}
		else if (ft_strcmp(lexer->cmd->str, "|") && (!tmp || tmp->type != token_cmd))
		{
			tokens = galloc(sizeof(t_token));
			if (tmp)
				tmp->next = tokens;
			if (i == 0)
				head = tokens;
			tokens->type = token_cmd;
			tokens->data = ft_calloc(1, sizeof(t_cmd));
			((t_cmd *)tokens->data)->cmd = lexer->cmd;
			((t_cmd *)tokens->data)->argv = ft_calloc(2, sizeof(t_word *));
			((t_cmd *)tokens->data)->argv[0] = lexer->cmd;
			((t_cmd *)tokens->data)->argv[1] = 0;
			((t_cmd *)tokens->data)->argc = 1;
			tokens->next = 0;
		}
		else if (ft_strcmp(lexer->cmd->str, "|") && tmp && tmp->type == token_cmd)
		{
			if (tmp->type == token_cmd)
			{
				((t_cmd *)tmp->data)->argv = ft_reallocf(((t_cmd *)tmp->data)->argv, (((t_cmd *)tmp->data)->argc) * sizeof(t_word *), (((t_cmd *)tmp->data)->argc + 2) * sizeof(t_word *));
				((t_cmd *)tmp->data)->argv[((t_cmd *)tmp->data)->argc] = lexer->cmd;
				((t_cmd *)tmp->data)->argv[((t_cmd *)tmp->data)->argc + 1] = 0;
				((t_cmd *)tmp->data)->argc++;
			}
		}
		else if (!ft_strcmp(lexer->cmd->str, "|"))
		{
			tokens = ft_calloc(1, sizeof(t_token));
			tmp->next = tokens;
			tokens->type = token_pipe;
			tokens->data = ft_calloc(1, sizeof(t_pipe));
			tokens->next = 0;
		}
		lexer = lexer->next;
	}
	return (head);
}

static void	print_tokens(t_token *tokens)
{
	char	*token_type;

	while (tokens)
	{
		printf("\ntoken %p\n", tokens);
		if (tokens->type == token_cmd)
			token_type = "token_cmd";
		else if (tokens->type == token_var)
			token_type = "token_var";
		else if (tokens->type == token_pipe)
			token_type = "token_pipe";
		else if (tokens->type == token_stdin)
			token_type = "token_stdin";
		else if (tokens->type == token_stdout)
			token_type = "token_stdout";
		else if (tokens->type == token_and)
			token_type = "token_and";
		else if (tokens->type == token_or)
			token_type = "token_or";
		else if (tokens->type == token_grp)
			token_type = "token_grp";
		printf("type: %s\n", token_type);
		printf("next: %p\n", tokens->next);
		if (tokens->type == token_cmd)
		{
			t_cmd	*cmd = (t_cmd *)tokens->data;
			printf("cmd: ");
			t_word	*tmp = cmd->cmd;
			while (tmp)
			{
				printf("%s", tmp->str);
				tmp = tmp->next;
			}
			printf("\n");
			printf("argv: ");
			for (int i = 0; cmd->argv[i]; i++)
				printf("\"%s\", ", cmd->argv[i]->str);
		}
		printf("\n");
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	*minishell;
	t_token		*token;

	minishell = init_minishell(argc, argv, envp);
	while (true)
	{
		input = prompt(minishell);
		if (!input)
			crash_exit();
		token = shitty_quick_tokenizer(lexer(input));
		if (!token)
		{
			gfree(input);
			continue ;
		}
		if (argv[1] && !ft_strcmp(argv[1], "debug"))
			print_tokens(token);
		executor(token);
		gfree(input);
	}
	exit (0);
}
