/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astnode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:26 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/01 16:20:04 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_astnode	*new_astnode(char **args, t_type type)
{
	t_astnode	*astnode;

	astnode = galloc(sizeof(t_astnode));
	if (!astnode || !args)
		return (0);
	astnode->l_node = 0;
	astnode->r_node = 0;
	astnode->args = args;
	astnode->type = type;
	return (astnode);
}
