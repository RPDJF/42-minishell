#include "env.h"

char	**var_to_tab(void)
{
	t_minishell	*minishell;
	t_var		*var;
	char		**tab;
	int			i;

	minishell = get_minishell();
	var = minishell->mini_envp;
	tab = 0;
	i = 0;
	while (var)
	{
		tab = ft_reallocf(tab, i * sizeof(char *), (i + 1) * sizeof(char *));
		if (!tab)
			crash_exit();
		tab[i] = ft_strsjoin(3, var->name, "=", var->value);
		var = var->next;
		i++;
	}
	tab = ft_reallocf(tab, i * sizeof(char *), (i + 1) * sizeof(char *));
	if (!tab)
		crash_exit();
	tab[i] = 0;
	return (tab);
}

void	print_minienvp(void)
{
	t_minishell	*minishell;
	t_var		*var;

	minishell = get_minishell();
	var = minishell->mini_envp;
	while (var)
	{
		if (var->is_env)
		{
			ft_putstr_fd(var->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd((char *)var->value, STDOUT_FILENO);
		}
		var = var->next;
	}
}
