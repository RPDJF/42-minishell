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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	char		*input;
	t_tlex		*lex;
	t_token		*token;

	minishell = init_minishell(argc, argv, envp);
	while (true)
	{
		input = prompt(minishell);
		if (!input)
			crash_exit();
		lex = lexer(input);
		if (!lex)
		{
			gfree(input);
			continue ;
		}
		print_lex(lex);
		// printf("expanded node[0]--->[%s]\n", parse_words(lex->cmd));
		token = parsing(&lex);
		ft_printf("token addr: %p\n", token);
		gfree(input);
	}
	exit (0);
}
