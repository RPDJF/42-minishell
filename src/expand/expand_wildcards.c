#include "expand_words.h"
#include <stdio.h>

int	to_next_wildcard(char *arg, char *str, int *i, int *j)
{
	if (str[*j] == '*')
	{
		while (str[*j] == '*')
			(*j)++;
		while (arg[*i] && arg[*i] != str[*j])
			(*i)++;
	}
	else if (*i > 0)
		while (arg[*i] && arg[*i] != str[*j])
			(*i)++;
	if (arg[*i] != str[*j] || !arg[*i])
		return (0);
	while (arg[*i] && str[*j] && arg[*i] == str[*j])
	{
		(*i)++;
		(*j)++;
		if (str[*j] == '*')
		{
			while (str[*j] && str[*j + 1] && str[*j + 1] == '*')
				(*j)++;
			return (1);
		}
	}
	return (1);
}

int	finish_wildcard(char *arg, char *str, int *i, int *j)
{
	int	k;
	int	l;

	l = ft_strlen(str);
	k = ft_strlen(arg);
	while (k >= *i && l > *j && arg[k] == str[l])
	{
		l--;
		k--;
	}
	if (str[l] == '*')
		return (1);
	return (0);
}

int	is_wildcard(char *arg, char *str, int i, int j)
{
	if ((only_wildcard(str) && arg[0] == '.') || ((arg[0] == '.')
			&& str[0] != '.') || (arg[0] == '.' && !arg[1])
		|| (arg[0] == '.' && arg[1] == '.' && !arg[2]))
		return (0);
	if (only_wildcard(str))
		return (1);
	while (str[j])
	{
		if (!is_last_wildcard(str + j))
			if (!to_next_wildcard(arg, str, &i, &j))
				return (0);
		if (is_last_wildcard(str + j))
			return (finish_wildcard(arg, str, &i, &j));
	}
	return (0);
}

char	**pars_wildcard(char *str)
{
	char	**arg;
	char	**tmp;
	int		i;

	i = -1;
	tmp = NULL;
	arg = get_files();
	replace_wildcard(arg, 1);
	while (arg[++i])
		if (is_wildcard(arg[i], str, 0, 0))
			tmp = strr_realloc(tmp, arg[i]);
	replace_wildcard(tmp, 0);
	return (tmp);
}

char	**parse_words_arr(t_word **words)
{
	char	**arr;
	char	**wld;
	size_t	j;
	size_t	i;

	arr = NULL;
	wld = NULL;
	j = -1;
	i = -1;
	while (i++, words[++j])
	{
		arr = strr_realloc(arr, parse_words(words[j]));
		if (ft_strchr(arr[i], '*'))
		{
			wld = pars_wildcard(arr[i]);
			if (wld)
				realloc_arr(&arr, wld, &i);
		}
	}
	replace_wildcard(arr, 0);
	return (arr);
}
