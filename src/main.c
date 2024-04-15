#include "minishell.h"
#include "prompter/prompt.h"
#include "parsing/parsing.h"
#include "lexer/lexer.h"
#include "utils/exit_handler.h"
#include "utils/expand_words.h"

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
				ft_printf("--->[%s:%d]", tmp2->str, tmp2->is_var);
				tmp2 = tmp2->next;
			}
			i++;
			ft_printf("\n");
		}
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
		print_lex(lex);
		if (!lex)
			continue ;
		printf("expanded node[0]--->[%s]\n", parse_words(lex->cmd));
		parsing(&lex);
		gfree(input);
	}
	exit (0);
}
