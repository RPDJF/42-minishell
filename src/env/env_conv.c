#include "env.h"
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
