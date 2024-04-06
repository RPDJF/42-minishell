/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:41:37 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/05 15:44:46 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

void	single_quote(t_lex *lex, char *input, char ***str)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (input[lex->j] && input[lex->j] != 39)
		lex->j++;
	word = ft_calloc((lex->j - lex->i) + 1, sizeof(char));
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		k++;
		lex->i++;
	}
	*str = strr_realloc(*str, word);
	gfree(word);
}

void	double_quote(t_lex *lex, char *input, char ***str)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (ft_isspace(input[lex->j]) == 0 && ft_isprint(input[lex->j]) == 1)
		lex->j++;
	word = ft_calloc((lex->j - lex->i) + 1, sizeof(char));
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		k++;
		lex->i++;
	}
	*str = strr_realloc(*str, word);
	gfree(word);
}

void	add_word_to_lex(t_lex *lex, char *input, char ***str)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (ft_isspace(input[lex->j]) == 0 && ft_isprint(input[lex->j]) == 1)
		lex->j++;
	word = ft_calloc((lex->j - lex->i) + 1, sizeof(char));
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		k++;
		lex->i++;
	}
	*str = strr_realloc(*str, word);
	gfree(word);
}

char	**lexer(char *input)
{
	t_lex	lex;
	char	**str;

	str = NULL;
	ft_bzero(&lex, sizeof(t_lex));
	while (input[lex.i])
	{
		while (ft_isspace(input[lex.i]) == 1)
			lex.i++;
		if (input[lex.i] == 39)
			single_quote(&lex, input, &str);
		if (input[lex.i] == 34)
			double_quote(&lex, input, &str);
		else
			add_word_to_lex(&lex, input, &str);
	}
	return (str);
}
