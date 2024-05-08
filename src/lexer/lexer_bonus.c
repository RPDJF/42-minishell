/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:27 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:26:28 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	delem(t_lex *lex, char *input, t_tlex **tlex)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (ft_isdelem(input, lex->j) == 1)
		lex->j++;
	if (ft_isdelem(input, lex->i) == 3)
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
	tword_add_back(tlex, tword_new(word, false, false));
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
	tword_add_back(tlex, tword_new(word, false, false));
	lex->i = lex->j;
}
