#include "minishell.h"
#include "prompter/prompt.h"
#include "parsing/parsing.h"
#include "lexer/lexer.h"
#include "utils/exit_handler.h"
#include "executor/executor.h"

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

void	print_lex(t_tlex *lex)
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
				ft_printf("--->[%s:%d:%d]", tmp2->str, \
					tmp2->is_var, tmp2->is_quoted);
				tmp2 = tmp2->next;
			}
			i++;
			ft_printf("\n");
		}
	}
}

t_token	*tokenizer(char	*input)
{
	t_tlex		*lex;
	t_token		*token;

	lex = lexer(input);
	if (!lex)
		return (NULL);
	print_lex(lex);
	token = parsing(&lex);
	if (!token)
		return (NULL);
	return (token);
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
		token = tokenizer(input);
		if (!token)
		{
			gfree(input);
			continue ;
		}
		print_tokens(token);
		executor(token);
		gfree(input);
	}
	exit (0);
}
