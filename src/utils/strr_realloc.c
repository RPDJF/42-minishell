#include "../lexer/lexer.h"
#include "exit_handler.h"

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
	if (!tab)
		crash_exit();
	while (i > 0 && j < i)
	{
		tab[j] = str[j];
		j++;
	}
	tab[j] = ft_strdup(neww);
	if (!tab[j])
		crash_exit();
	gfree(str);
	return (tab);
}
