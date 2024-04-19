#include "env.h"

char	**var_to_tab(void)
{
	t_var		*var;
	char		**tab;
	int			i;

	var = get_minishell()->mini_envp;
	tab = 0;
	i = 0;
	while (var)
	{
		if (var->is_env)
		{
			tab = ft_reallocf(tab, i * sizeof(char *),
					(i + 1) * sizeof(char *));
			if (!tab)
				crash_exit();
			tab[i] = ft_strsjoin(3, var->name, "=", var->value);
			i++;
		}
		var = var->next;
	}
	tab = ft_reallocf(tab, i * sizeof(char *), (i + 1) * sizeof(char *));
	if (!tab)
		crash_exit();
	tab[i] = 0;
	return (tab);
}

static t_var	**var_to_vartab(void)
{
	t_var	**vars;
	t_var	*var;
	int		size;

	var = get_minishell()->mini_envp;
	size = -1;
	while (++size, var)
		var = var->next;
	vars = galloc((size + 1) * sizeof(t_var *));
	if (!vars)
		crash_exit();
	var = get_minishell()->mini_envp;
	size = -1;
	while (++size, var)
	{
		vars[size] = var;
		var = var->next;
	}
	vars[size] = 0;
	return (vars);

}

static t_var	**sorted_vartab(void)
{
	t_var	**vars_export;
	t_var	*vars;
	int		size;

	vars_export = var_to_vartab();
	vars = get_minishell()->mini_envp;
	size = -1;
	while (++size, vars)
	{
		vars = vars->next;
		if (size && vars_export[size - 1])
		{
			if (ft_strcmp(vars_export[size - 1]->name,
					vars_export[size]->name) > 0)
			{
				vars = vars_export[size];
				vars_export[size] = vars_export[size - 1];
				vars_export[size - 1] = vars;
				size = -1;
				vars = get_minishell()->mini_envp;
			}
		}
	}
	return (vars_export);
}

void	print_export(void)
{
	t_var		**head;
	t_var		**vars;

	vars = sorted_vartab();
	head = vars;
	while (*vars)
	{
		if ((*vars)->is_env && ft_strcmp((*vars)->name, "_"))
		{
			printf("declare -x %s", (*vars)->name);
			if ((*vars)->value)
				printf("=\"%s\"\n", (*vars)->value);
			else
				printf("\n");
		}
		vars++;
	}
	gfree(head);
}

void	print_minienvp(void)
{
	t_minishell	*minishell;
	t_var		*var;

	minishell = get_minishell();
	var = minishell->mini_envp;
	while (var)
	{
		if (var->is_env && var->value)
			printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
}
