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
	t_token *head;
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
		if (ft_strcmp(lexer->cmd->str, "|") && (!tmp || (tmp->type != token_cmd && tmp->type != token_builtin)))
		{
			tokens = galloc(sizeof(t_token));
			if (tmp)
				tmp->next = tokens;
			if (i == 0)
				head = tokens;
			if (!ft_strcmp (lexer->cmd->str, "cd"))
			{
				tokens->type = token_builtin;
				tokens->data = ft_calloc(1, sizeof(t_builtin));
				((t_builtin *)tokens->data)->cmd = builtin_cd;
				((t_builtin *)tokens->data)->argv = ft_calloc(2, sizeof(t_word *));
				((t_builtin *)tokens->data)->argv[0] = lexer->cmd;
				((t_builtin *)tokens->data)->argv[1] = 0;
				((t_builtin *)tokens->data)->argc = 1;
			}
			else if (!ft_strcmp(lexer->cmd->str, "echo"))
			{
				tokens->type = token_builtin;
				tokens->data = ft_calloc(1, sizeof(t_builtin));
				((t_builtin *)tokens->data)->cmd = builtin_echo;
				((t_builtin *)tokens->data)->argv = ft_calloc(2, sizeof(t_word *));
				((t_builtin *)tokens->data)->argv[0] = lexer->cmd;
				((t_builtin *)tokens->data)->argv[1] = 0;
				((t_builtin *)tokens->data)->argc = 1;
			}
			else if (!ft_strcmp(lexer->cmd->str, "exit"))
			{
				tokens->type = token_builtin;
				tokens->data = ft_calloc(1, sizeof(t_builtin));
				((t_builtin *)tokens->data)->cmd = builtin_exit;
				((t_builtin *)tokens->data)->argv = ft_calloc(2, sizeof(t_word *));
				((t_builtin *)tokens->data)->argv[0] = lexer->cmd;
				((t_builtin *)tokens->data)->argv[1] = 0;
				((t_builtin *)tokens->data)->argc = 1;
			}
			else if (!ft_strcmp(lexer->cmd->str, "export"))
			{
				tokens->type = token_builtin;
				tokens->data = ft_calloc(1, sizeof(t_builtin));
				((t_builtin *)tokens->data)->cmd = builtin_export;
				((t_builtin *)tokens->data)->argv = ft_calloc(2, sizeof(t_word *));
				((t_builtin *)tokens->data)->argv[0] = lexer->cmd;
				((t_builtin *)tokens->data)->argv[1] = 0;
				((t_builtin *)tokens->data)->argc = 1;
			}
			else if (!ft_strcmp(lexer->cmd->str, "pwd"))
			{
				tokens->type = token_builtin;
				tokens->data = ft_calloc(1, sizeof(t_builtin));
				((t_builtin *)tokens->data)->cmd = builtin_pwd;
				((t_builtin *)tokens->data)->argv = ft_calloc(2, sizeof(t_word *));
				((t_builtin *)tokens->data)->argv[0] = lexer->cmd;
				((t_builtin *)tokens->data)->argv[1] = 0;
				((t_builtin *)tokens->data)->argc = 1;
			}
			else
			{
				tokens->type = token_cmd;
				tokens->data = ft_calloc(1, sizeof(t_cmd));
				((t_cmd *)tokens->data)->cmd = lexer->cmd;
				((t_cmd *)tokens->data)->argv = ft_calloc(2, sizeof(t_word *));
				((t_cmd *)tokens->data)->argv[0] = lexer->cmd;
				((t_cmd *)tokens->data)->argv[1] = 0;
				((t_cmd *)tokens->data)->argc = 1;
			}
			if (!tmp)
				tokens->prev = 0;
			else
				tokens->prev = tmp;
			tokens->next = 0;
			lexer = lexer->next;
			continue ;
		}
		else if (ft_strcmp(lexer->cmd->str, "|") && tmp && (tmp->type == token_cmd || tmp->type == token_builtin))
		{
			if (tmp->type == token_cmd)
			{
				((t_cmd *)tmp->data)->argv = ft_reallocf(((t_cmd *)tmp->data)->argv, (((t_cmd *)tmp->data)->argc) * sizeof(t_word *), (((t_cmd *)tmp->data)->argc + 2) * sizeof(t_word *));
				((t_cmd *)tmp->data)->argv[((t_cmd *)tmp->data)->argc] = lexer->cmd;
				((t_cmd *)tmp->data)->argv[((t_cmd *)tmp->data)->argc + 1] = 0;
				((t_cmd *)tmp->data)->argc++;
			}
			else if (tmp->type == token_builtin)
			{
				((t_builtin *)tmp->data)->argv = ft_reallocf(((t_builtin *)tmp->data)->argv, (((t_builtin *)tmp->data)->argc) * sizeof(t_word *), (((t_builtin *)tmp->data)->argc + 2) * sizeof(t_word *));
				((t_builtin *)tmp->data)->argv[((t_builtin *)tmp->data)->argc] = lexer->cmd;
				((t_builtin *)tmp->data)->argv[((t_builtin *)tmp->data)->argc + 1] = 0;
				((t_builtin *)tmp->data)->argc++;
			}
		}
		else if (!ft_strcmp(lexer->cmd->str, "|"))
		{
			tokens = ft_calloc(1, sizeof(t_token));
			tmp->next = tokens;
			tokens->type = token_pipe;
			tokens->data = ft_calloc(1, sizeof(t_pipe));
			tokens->prev = tmp;
			tokens->next = 0;
		}
		lexer = lexer->next;
	}
	return (head);
}

static void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("token n°%p\n", tokens);
		printf("type: %d\n", tokens->type);
		printf("prev: %p\n", tokens->prev);
		printf("next: %p\n", tokens->next);
		if (tokens->type == token_cmd)
		{
			printf("cmd: %s\n", ((t_cmd *)tokens->data)->cmd->str);
			for (int i = 0; ((t_cmd *)tokens->data)->argv[i]; i++)
				printf("argv[%d]: %s\n", i, ((t_cmd *)tokens->data)->argv[i]->str);
		}
		printf("\n\n");
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
