/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:41:37 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/14 01:26:09 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isdelem(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	if ((str[i] == '&' && str[i + 1] == '&') || \
		(str[i] == '|' && str[i + 1] == '|'))
		return (2);
	return (0);
}

int	impair_pair_char(char *str, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	if (count % 2 == 0)
		return (0);
	return (1);
}

void	delem(t_lex *lex, char *input, t_tlex **tlex)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (ft_isdelem(input, lex->j) == 1)
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
	tword_add_back(tlex, tword_new(word, false));
	lex->i = lex->j;
}

void	delem_bonus(t_lex *lex, char *input, t_tlex **tlex)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (input[lex->j] == '&')
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
	tword_add_back(tlex, tword_new(word, false));
	lex->i = lex->j;
}

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
	tword_add_back(tlex, tword_new(word, ft_strchr(word, '$')));
}

void	words_lexing(t_lex *lex, char *input, t_tlex **tlex)
{
	t_tlex	*new_tlex;

	new_tlex = ft_calloc(1, sizeof(t_tlex));
	if (!new_tlex)
		crash_exit();
	while (input[lex->i] && (input[lex->i] == 39 || input[lex->i] == 34 || \
		ft_isdelem(input, lex->i) == 1 || ft_isdelem(input, lex->i) == 2 \
			|| ft_isspace(input[lex->i]) == 0))
	{
		if (input[lex->i] == 39)
			single_quote(lex, input, &new_tlex);
		else if (input[lex->i] == 34)
			double_quote(lex, input, &new_tlex);
		else if (ft_isdelem(input, lex->i) == 1)
			delem(lex, input, &new_tlex);
		else if (ft_isdelem(input, lex->i) == 2)
			delem_bonus(lex, input, &new_tlex);
		else if (ft_isspace(input[lex->i]) == 0)
			add_word_to_lex_str(lex, input, &new_tlex);
		else
			break ;
	}
	if (new_tlex && new_tlex->cmd)
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
