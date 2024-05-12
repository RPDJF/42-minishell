/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:30:31 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/12 17:12:05 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	free_all(t_token **token, t_tlex **lex)
{
	t_tlex	*tmp1;
	t_token	*tmp2;

	while (*lex)
	{
		if ((*lex)->cmd)
			free_tword((*lex)->cmd);
		tmp1 = (*lex);
		*lex = (*lex)->next;
		gfree(tmp1);
	}
	while ((*token))
	{
		gfree((*token)->data);
		tmp2 = *token;
		*token = (*token)->next;
		gfree(tmp2);
	}
}
