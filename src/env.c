/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:13:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/13 23:15:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_var	*add_var(t_var **head, t_var *var)
{
	t_var	*tmp;

	if (!head || !*head)
	{
		*head = var;
		return (var);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = var;
	var->prev = tmp;
	return (var);
}

void	*parse_var(char *var_name)
{
	char	*env;
	char	*output;

	if (!ft_strcmp(var_name, "SHLVL"))
	{
		env = getenv("SHLVL");
		if (!env)
			output = ft_strdup("1");
		else
			output = ft_itoa(ft_atoi(env) + 1);
	}
	else if (!ft_strcmp(var_name, "PWD"))
		output = getcwd(0, 0);
	else
		output = ft_strdup(getenv(var_name));
	if (!output)
		crash_exit();
	return (output);
}

// TO DO: DETECT IF ENVP VALUE IS TOKEN OR STRING

t_var	*init_minienvp(t_minishell *minishell)
{
	t_var	*var;
	t_var	*head;
	int		i;

	i = 0;
	head = 0;
	while (minishell->envp[i])
	{
		var = galloc(sizeof(t_var));
		var->prev = 0;
		var->next = 0;
		if (!var)
			crash_exit();
		var->name = ft_substr(minishell->envp[i], 0,
				ft_strchr(minishell->envp[i], '=') - minishell->envp[i]);
		var->type = var_str;
		var->data = parse_var(var->name);
		if (!var->name || !var->data)
			crash_exit();
		add_var(&head, var);
		i++;
	}
	return (head);
}

// TO DO: DETECT IF ENVP VALUE IS TOKEN OR STRING

char	**var_to_tab(t_var *var)
{
	char	**tab;
	int		i;

	tab = 0;
	i = 0;
	while (var)
	{
		tab = ft_reallocf(tab, i * sizeof(char *), (i + 1) * sizeof(char *));
		if (!tab)
			crash_exit();
		if (var->type == var_str)
			tab[i] = ft_strsjoin(3, var->name, "=", var->data);
		var = var->next;
		i++;
	}
	tab = ft_reallocf(tab, i * sizeof(char *), (i + 1) * sizeof(char *));
	if (!tab)
		crash_exit();
	tab[i] = 0;
	return (tab);
}

// TO DO: DETECT IF ENVP VALUE IS TOKEN OR STRING

void	print_minienvp(t_var *var)
{
	while (var)
	{
		ft_putstr_fd(var->name, 1);
		ft_putstr_fd("=", 1);
		if (var->type == var_str)
			ft_putendl_fd((char *)var->data, 1);
		var = var->next;
	}
}
