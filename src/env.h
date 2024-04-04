/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:13:21 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/03 13:40:03 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

//	t_var: linked list structure for mini_envp
//	return: t_var pointer to the head of the var
t_var	*add_var(t_var **head, t_var *var);
//	init_minienvp: initialize mini_envp from envp in minishell
//	return: t_var pointer to the head of the mini_envp
t_var	*init_minienvp(t_minishell *minishell);
//	var_to_tab: convert mini_envp to char **tab
//	need to free the returned tab
//	meant to be used in execve, so it will be freed by the kernel
//	return: char **tab
char	**var_to_tab(t_var *var);
//	print_minienvp: print mini_envp
void	print_minienvp(t_var *var);

#endif