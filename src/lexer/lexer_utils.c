/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:34 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:26:35 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <unistd.h>
#include "../env/env.h"

int	ft_isdelem(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	if ((str[i] == '&' && str[i + 1] == '&') || \
		(str[i] == '|' && str[i + 1] == '|'))
		return (2);
	if (str[i] == '(' || str[i] == ')')
		return (3);
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

int	exit_print(char *str, int exitcode)
{
	error_msg((char *[]){APP_NAME, "lexer", 0}, str);
	update_exitcode(exitcode);
	return (1);
}

t_tlex	*free_exit_lexer(t_tlex **tlex)
{
	t_tlex	*tmp1;
	t_word	*tmp2;
	t_word	*tmp3;

	tmp1 = *tlex;
	while (tmp1)
	{
		tmp2 = tmp1->cmd;
		while (tmp2)
		{
			if (tmp2->str)
				gfree(tmp2->str);
			tmp3 = tmp2;
			tmp2 = tmp2->next;
			if (tmp3)
				gfree(tmp3);
		}
		tmp1 = tmp1->next;
	}
	return (NULL);
}
