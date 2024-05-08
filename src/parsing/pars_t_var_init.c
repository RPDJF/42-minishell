/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_t_var_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:49 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:26:51 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../builtin/export.h"

int	correct_syntax_var(char *str)
{
	if (*str && (ft_isdigit(*str) || !ft_isalpha(*str)))
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

t_word	*get_value_ofvar(char *str)
{
	t_word	*arg;

	arg = ft_calloc(1, sizeof(t_word));
	if (!arg)
		crash_exit();
	arg->str = ft_strdup(ft_strchr(str, '=') + 1);
	return (arg);
}

int	tk_is_var_init(t_token *neww, t_pars *pars)
{
	neww->data = (t_var_init *)ft_calloc(1, sizeof(t_var_init));
	if (!neww->data)
		crash_exit();
	neww->type = token_var;
	((t_var_init *)(neww)->data)->name = var_name(pars->tmp1->cmd->str);
	((t_var_init *)(neww)->data)->value = get_value_ofvar(pars->tmp1->cmd->str);
	((t_var_init *)(neww)->data)->value->next = pars->tmp1->cmd->next;
	pars->tmp1 = pars->tmp1->next;
	return (1);
}
