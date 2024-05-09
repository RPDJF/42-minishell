/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:36 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/09 18:08:11 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_cmd(t_cmd	*data)
{
	int		i;

	i = -1;
	if (!data)
		return ;
	if (data->cmd)
		free_tword(data->cmd);
	while (*(data->argv) && data->argv[++i])
		free_tword(data->argv[i]);
	if (*(data)->argv)
		gfree(*(data)->argv);
	gfree(data);
}

void	free_stdout(t_stdout *data_stdout)
{
	if (data_stdout->filename)
		gfree(data_stdout->filename);
	gfree(data_stdout);
}

void	free_stdin(t_stdin *data_stdin)
{
	if (data_stdin->filename)
		gfree(data_stdin->filename);
	if (data_stdin->limiter)
		gfree(data_stdin->limiter);
	gfree(data_stdin);
}

void	free_is_var(t_var_init *data)
{
	if (data->name)
		gfree(data->name);
	if (data->value)
		free_tword(data->value);
	gfree(data);
}

t_token	*free_exit_token(t_token **token, t_tlex **lex)
{
	t_token	*tmp1;
	t_token	*tmp2;

	(void)lex;
	tmp1 = *token;
	while (tmp1)
	{
		if (tmp1->type == token_cmd)
			free_cmd((t_cmd *)tmp1->data);
		else if (tmp1->type == token_stdout)
			free_stdout((t_stdout *)tmp1->data);
		else if (tmp1->type == token_stdin)
			free_stdin((t_stdin *)tmp1->data);
		else if (tmp1->type == token_var)
			free_is_var((t_var_init *)tmp1->data);
		else if (tmp1->data)
			gfree(tmp1->data);
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		gfree(tmp2);
	}
	return (NULL);
}
