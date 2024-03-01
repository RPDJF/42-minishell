/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   faker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:17:12 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/01 17:24:18 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_astnode	*generate_fake_ast(void)
{
	t_astnode	*astnode;
	t_astnode	*tmp;
	t_astnode	*tmp2;

	astnode = new_astnode(ft_split("|", ' '), e_pipe);
	if (!astnode)
		return (0);
	tmp = new_astnode(ft_split("echo a", ' '), e_cmd);
	if (!tmp)
		return (0);
	astnode->l_node = tmp;
	tmp = new_astnode(ft_split("|", ' '), e_pipe);
	if (!tmp)
		return (0);
	astnode->r_node = tmp;
	tmp2 = new_astnode(ft_split("echo b", ' '), e_cmd);
	if (!tmp2)
		return (0);
	tmp->l_node = tmp2;
	tmp2 = new_astnode(ft_split("echo c", ' '), e_cmd);
	if (!tmp2)
		return (0);
	tmp->r_node = tmp2;
	return (astnode);
}
