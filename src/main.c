#include "minishell.h"
#include "prompter/prompt.h"
#include "parsing/parsing.h"
#include "lexer/lexer.h"
#include "utils/exit_handler.h"

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
	token = parsing(lex);
	if (!token)
		return (NULL);
	ft_printf("token addr: %p\n", token);
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
		gfree(input);
	}
	exit (0);
}
