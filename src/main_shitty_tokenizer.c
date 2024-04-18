#include "minishell.h"
#include "prompter/prompt.h"
#include "parsing/parsing.h"
#include "lexer/lexer.h"
#include "utils/exit_handler.h"
#include "utils/expand_words.h"
#include "executor/executor.h"

static void	print_lex(t_tlex *lex)
{
	int		i;
	t_word	*tmp2;

	i = 0;
	if (lex)
	{
		for (t_tlex *tmp1 = lex; tmp1; tmp1 = tmp1->next)
		{
			ft_printf("noeud[%d]", i);
			tmp2 = tmp1->cmd;
			while (tmp2)
			{
				ft_printf("--->[%s:%d]", tmp2->str, tmp2->is_var);
				tmp2 = tmp2->next;
			}
			i++;
			ft_printf("\n");
		}
	}
}

static t_token	*shitty_quick_tokenizer(t_tlex *lexer)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*tokens;
	int	i;

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
		if (ft_strcmp(lexer->cmd->str, "|") && (!tmp || tmp->type != token_cmd))
		{
			printf("NOON\n");
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
			lexer = lexer->next;
			continue ;
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
	t_minishell	*minishell;
	char		*input;
	t_tlex		*lex;

	minishell = init_minishell(argc, argv, envp);
	while (true)
	{
		input = prompt(minishell);
		if (!input)
			crash_exit();
		lex = lexer(input);
		if (!lex)
			continue ;
		if (argv[1] && !ft_strcmp(argv[1], "debug"))
			print_lex(lex);
		t_token	*tokens;
		tokens = shitty_quick_tokenizer(lex);
		if (argv[1] && !ft_strcmp(argv[1], "debug"))
			print_tokens(tokens);
		executor(tokens);
		parsing(&lex);
		gfree(input);
	}
	exit (0);
}
