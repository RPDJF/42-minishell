#include "expand_words.h"

int	is_last_wildcard(char *str)
{
	if (*str == '*')
		str++;
	while (*str)
	{
		if (*str == '*')
			return (0);
		str++;
	}
	return (1);
}

void	replace_wildcard(char **str, bool rpls)
{
	int	i;
	int	j;

	i = -1;
	while (str && str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '*' && rpls)
				str[i][j] = 5;
			if (str[i][j] == 5 && !rpls)
				str[i][j] = '*';
		}
	}
}

int	only_wildcard(char *str)
{
	while (*str == '*')
		str++;
	if (!*str)
		return (1);
	return (0);
}

void	realloc_arr(char ***arr, char **wld, size_t *i)
{
	int	j;

	j = 0;
	if (!*arr[0])
		return ;
	gfree(arr[0][*i]);
	arr[0][*i] = NULL;
	while (wld && wld[j])
	{
		*arr = strr_realloc(*arr, wld[j]);
		gfree(wld[j]);
		j++;
	}
	while (arr[0][*i + 1])
		*i += 1;
}
