#include "minishell.h"
#include "prompter/prompt.h"
#include "parsing/parsing.h"
#include "lexer/lexer.h"
#include "executor/executor.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*token;
	t_tlex		*lex;

	while (true)
	{
		input = prompt(init_minishell(argc, argv, envp));
		lex = lexer(input);
		if (!lex)
			continue ;
		token = parsing(&lex);
		if (!token)
			continue ;
		executor(token);
		free_all(&token, &lex);
	}
}
