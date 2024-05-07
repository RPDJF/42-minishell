#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

//	Macros
# define DEFAULT_PATH "/usr/local/bin:/usr/local/sbin:\
/usr/bin:/usr/sbin:/bin:/sbin:."

//	new_var: create a new variable
//	return: t_var pointer to the new variable
t_var	*new_var(char *name, char *value, bool is_env, bool is_name_alloc);
//	destroy_var: free a variable
void	destroy_var(t_var *var);
//	remove_var: remove and destroy a variable from mini_envp
void	remove_var(t_var *var);
//	get_envp_value: get a value from envp
//	return: char *value or 0 if not found
char	*get_envp_value(char *name, char **envp);
//	get_var: get a variable from mini_envp
//	return: t_var pointer to the variable or 0 if not found
t_var	*get_var(char *name);
//	get_var_value: get the string value of a variable from mini_envp
//	return: allocated char *value or "" if not found
char	*get_var_value(char *name);
//	update_var: update a variable in mini_envp
//	if the variable does not exist, it will be added to the end of the list
//	return: t_var pointer to the updated variable
t_var	*update_var(t_var *var);
//	add_var: add a variable to the end of the list
//	it does not check for duplicates, use update_var if not sure
//	return: t_var pointer to the added variable
t_var	*add_var(t_var *var);
//	init_minienvp: initialize mini_envp from envp in minishell
//	return: t_var pointer to the head of the mini_envp
t_var	*init_minienvp(void);
//	var_to_tab: convert mini_envp to char **tab
//	need to free the returned tab
//	meant to be used in execve, so it will be freed by the kernel
//	return: char **tab
char	**var_to_tab(void);
//	print_export: print export
void	print_export(void);
//	print_minienvp: print mini_envp
void	print_minienvp(void);
//	update_exitcode: update the exit code variable
void	update_exitcode(int exitcode);
//	update_dash: update the dash variable
void	update_dash(char *value);

#endif