#include "../lexer/lexer.h"

char	**strr_realloc(char **str, char *neww)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str)
		while (str[i] != NULL)
			i++;
	tab = ft_calloc(i + 2, sizeof(char *));
	while (i > 0 && j < i)
	{
		tab[j] = ft_strdup(str[j]);
		j++;
	}
	tab[j] = ft_strdup(neww);
	if (str && *str)
		ft_free_tab(str);
	return (tab);
}
