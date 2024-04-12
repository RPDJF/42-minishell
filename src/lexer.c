/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:41:37 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/12 14:43:16 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

int	ft_isdelem(char *str)
{
	while (*str)
	{
		if (*str == '|' || *str == '>' || *str == '<')
			return (1);
		if (*str == '&' && *str + 1 == '&')
			return (1);
		str++;
	}
	return (0);
}

int	impair_impar_char(char *str, char c)
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

void	end_single_quote(t_lex *lex, char *input, char ***str, char *word)
{
	int	k;

	k = 0;
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		lex->i++;
		k++;
	}
	*str = strr_realloc(*str, word);
	gfree(word);
	while (input[lex->i] == 39)
		lex->i++;
}

void	single_quote(t_lex *lex, char *input, char ***str)
{
	char	*word;
	int		k;

	k = 0;
	if (impair_impar_char(input, 39) == 1)
		error_exit(NULL, "fdf: bad single_quote format", 127);
	while (input[lex->i] == 39)
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
	word = ft_calloc(k + 1, sizeof(char));
	end_single_quote(lex, input, str, word);
}

void	end_double_quote(t_lex *lex, char *input, char ***str, char *word)
{
	int	k;

	k = 0;
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		lex->i++;
		k++;
	}
	*str = strr_realloc(*str, word);
	gfree(word);
	while (input[lex->i] == 34)
		lex->i++;
}

void	double_quote(t_lex *lex, char *input, char ***str)
{
	char	*word;
	int		k;

	k = 0;
	if (impair_impar_char(input, 34) == 1)
		error_exit(NULL, "fdf: bad single_quote format", 127);
	while (input[lex->i] == 34)
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
	word = ft_calloc(k + 1, sizeof(char));
	end_double_quote(lex, input, str, word);
}

void	add_word_to_lex(t_lex *lex, char *input, char ***str)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (ft_isspace(input[lex->j]) == 0 && \
		ft_isprint(input[lex->j]) == 1 && input[lex->j] != 34 && \
			input[lex->j] != 39)
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
		if (input[lex.i] == 39 || input[lex.i] == 34)
		{
			if (input[lex.i] == 39)
				single_quote(&lex, input, &str);
			else if (input[lex.i] == 34)
				double_quote(&lex, input, &str);
		}
		else
			add_word_to_lex(&lex, input, &str);
	}
	return (str);
}
