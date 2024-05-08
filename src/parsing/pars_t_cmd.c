/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_t_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:44 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:26:46 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tk_cmd(t_token *neww, t_pars *pars)
{
	t_cmd	*data_tmp;

	neww->data = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!neww->data)
		crash_exit();
	data_tmp = neww->data;
	data_tmp->cmd = pars->tmp1->cmd;
	data_tmp->argv = ft_calloc(arg_count(pars->tmp1->next) + 2, sizeof(t_word));
	if (!data_tmp->argv)
		crash_exit();
	data_tmp->argv[0] = pars->tmp1->cmd;
	pars->tmp1 = pars->tmp1->next;
	if (!pars_arg_tk_cmd(neww, data_tmp, pars))
		return (0);
	return (1);
}
