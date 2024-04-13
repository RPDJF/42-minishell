/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:41:37 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/13 12:14:49 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

void	tlst_add_back(t_tlex **lst, t_tlex *neww)
{
	t_tlex	*tmp;

	if (!lst || !neww)
		return ;
	if (!*lst)
		*lst = neww;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = neww;
		neww->prev = tmp;
	}
}

t_tlex	*tlst_new(char *cmd, bool var)
{
	t_tlex	*p;

	p = calloc(1, sizeof(t_tlex));
	if (!p)
		return (0);
	p->cmd = cmd;
	p->var = var;
	p->next = NULL;
	p->prev = NULL;
	return (p);
}

int	ft_isdelem(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	if ((str[i] == '&' && str[i + 1] == '&') || \
		(str[i] == '|' && str[i + 1] == '|'))
		return (2);
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
	tlst_add_back(tlex, tlst_new(word, false));
	while (input[lex->i] == 39)
		lex->i++;
}

void	single_quote(t_lex *lex, char *input, t_tlex **tlex)
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
	tlst_add_back(tlex, tlst_new(word, false));
	while (input[lex->i] == 34)
		lex->i++;
}

void	double_quote(t_lex *lex, char *input, t_tlex **tlex)
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
	end_double_quote(lex, input, tlex, word);
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
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		k++;
		lex->i++;
	}
	tlst_add_back(tlex, tlst_new(word, false));
	lex->i = lex->j;
}

void	delem_bonus(t_lex *lex, char *input, t_tlex	**tlex)
{
	char	*word;
	int		k;

	k = 0;
	lex->j = lex->i;
	while (input[lex->j] == '&')
		lex->j++;
	word = ft_calloc((lex->j - lex->i) + 1, sizeof(char));
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		k++;
		lex->i++;
	}
	tlst_add_back(tlex, tlst_new(word, false));
	lex->i = lex->j;
}

void	add_word_to_lex(t_lex *lex, char *input, t_tlex **tlex)
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
	while (lex->i < lex->j)
	{
		word[k] = input[lex->i];
		k++;
		lex->i++;
	}
	tlst_add_back(tlex, tlst_new(word, false));
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
		if (input[lex.i] == 39 || input[lex.i] == 34 || \
			ft_isdelem(input, lex.i) == 1)
		{
			if (input[lex.i] == 39)
				single_quote(&lex, input, &tlex);
			else if (input[lex.i] == 34)
				double_quote(&lex, input, &tlex);
			else if (ft_isdelem(input, lex.i) == 1)
				delem(&lex, input, &tlex);
			else if (ft_isdelem(input, lex.i) == 2)
				delem_bonus(&lex, input, &tlex);
		}
		else if (ft_isspace(input[lex.i]) == 0 && input[lex.i] != '\0')
			add_word_to_lex(&lex, input, &tlex);
	}
	return (tlex);
}
