#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

//	get_var: get a variable from mini_envp
//	return: t_var pointer to the variable or 0 if not found
t_var	*get_var(t_minishell *minishell, char *name);
//	update_var: update a variable in mini_envp
//	if the variable does not exist, it will be added to the end of the list
//	return: t_var pointer to the updated variable
t_var	*update_var(t_minishell *ms, char *name, void *data, t_var_type type);
//	add_var: add a variable to the end of the list
//	it does not check for duplicates, use update_var if not sure
//	return: t_var pointer to the added variable
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