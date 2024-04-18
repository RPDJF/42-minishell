#include "lexer.h"
#include <unistd.h>

void	add_word_to_lex_str(t_lex *lex, char *input, t_tlex **tlex)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (ft_isspace(input[lex->j]) == 0 && \
		ft_isprint(input[lex->j]) == 1 && input[lex->j] != 34 && \
			input[lex->j] != 39 && ft_isdelem(input, lex->j) == 0)
		lex->j++;
	word = ft_calloc((lex->j - lex->i) + 1, sizeof(char));
	if (!word)
		crash_exit();
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		k++;
		lex->i++;
	}
	tword_add_back(tlex, tword_new(word, ft_strchr(word, '$'), false));
}

void	words_lexing(t_lex *lex, char *input, t_tlex **tlex)
{
	t_tlex	*new_tlex;

	new_tlex = ft_calloc(1, sizeof(t_tlex));
	if (!new_tlex)
		crash_exit();
	while (input[lex->i] && ft_isdelem(input, lex->i) == 0
		&& (input[lex->i] == 39 || input[lex->i] == 34
			|| ft_isspace(input[lex->i]) == 0))
	{
		if (input[lex->i] == 39)
			single_quote(lex, input, &new_tlex);
		else if (input[lex->i] == 34)
			double_quote(lex, input, &new_tlex);
		else if (ft_isspace(input[lex->i]) == 0)
			add_word_to_lex_str(lex, input, &new_tlex);
		else
			break ;
	}
	if (!new_tlex->cmd && ft_isdelem(input, lex->i) == 1)
		delem(lex, input, &new_tlex);
	else if (!new_tlex->cmd && ft_isdelem(input, lex->i) == 2)
		delem_bonus(lex, input, &new_tlex);
	if (new_tlex->cmd)
		tlex_add_back(tlex, new_tlex);
}

t_tlex	*lexer(char *input)
{
	t_lex	lex;
	t_tlex	*tlex;

	tlex = NULL;
	ft_bzero(&lex, sizeof(t_lex));
	while (input[lex.i])
	{
		while (ft_isspace(input[lex.i]) == 1)
			lex.i++;
		if (ft_isspace(input[lex.i]) == 0 || input[lex.i] == 39 || \
			input[lex.i] == 34 || ft_isdelem(input, lex.i) == 1 || \
			ft_isdelem(input, lex.i) == 2)
			words_lexing(&lex, input, &tlex);
	}
	return (tlex);
}
