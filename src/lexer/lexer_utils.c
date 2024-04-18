#include "lexer.h"

int	ft_isdelem(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	if ((str[i] == '&' && str[i + 1] == '&') || \
		(str[i] == '|' && str[i + 1] == '|'))
		return (2);
	return (0);
}

int	impair_pair_char(char *str, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	if (count % 2 == 0)
		return (0);
	return (1);
}
