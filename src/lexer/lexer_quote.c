#include "lexer.h"

int	count_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

void	end_single_quote(t_lex *lex, char *input, t_tlex **tlex, char *word)
{
	int	k;

	k = 0;
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		lex->i++;
		k++;
	}
	tword_add_back(tlex, tword_new(word, false));
	lex->i++;
}

void	single_quote(t_lex *lex, char *input, t_tlex **tlex)
{
	char	*word;
	int		k;

	k = 0;
	if (impair_pair_char(input, 39) == 1)
		error_exit(NULL, "minishell: bad single_quote format", 127);
	lex->i++;
	lex->j = lex->i;
	while (input[lex->j])
	{
		if (input[lex->j] == 39)
			break ;
		else
			k++;
		lex->j++;
	}
	if (lex->j == lex->i)
	{
		lex->i++;
		return ;
	}
	word = ft_calloc(k + 1, sizeof(char));
	if (!word)
		crash_exit();
	end_single_quote(lex, input, tlex, word);
}

void	end_double_quote(t_lex *lex, char *input, t_tlex **tlex, char *word)
{
	int	k;

	k = 0;
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		lex->i++;
		k++;
	}
	tword_add_back(tlex, tword_new(word, ft_strchr(word, '$')));
	lex->i++;
}

void	double_quote(t_lex *lex, char *input, t_tlex **tlex)
{
	char	*word;
	int		k;

	k = 0;
	if (impair_pair_char(input, 34) == 1)
		error_exit(NULL, "minishell: bad single_quote format", 127);
	lex->i++;
	lex->j = lex->i;
	while (input[lex->j])
	{
		if (input[lex->j] == 34)
			break ;
		else
			k++;
		lex->j++;
	}
	if (lex->j == lex->i)
	{
		lex->i++;
		return ;
	}
	word = ft_calloc(k + 1, sizeof(char));
	if (!word)
		crash_exit();
	end_double_quote(lex, input, tlex, word);
}
