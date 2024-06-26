/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:55 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:55 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	destroy_var(t_var *var)
{
	if (var->name)
		gfree(var->name);
	if (var->value)
		gfree(var->value);
	gfree(var);
}

void	remove_var(t_var *var)
{
	if (!var)
		return ;
	if (var->prev)
		var->prev->next = var->next;
	if (var->next)
		var->next->prev = var->prev;
	if (get_minishell()->mini_envp == var)
		get_minishell()->mini_envp = var->next;
	destroy_var(var);
}
