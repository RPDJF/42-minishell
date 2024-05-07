#include "expand_words.h"
#include <stdio.h>

static char	**get_files(void)
{
	char			pwd[PATH_MAX];
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i;

	getcwd(pwd, PATH_MAX);
	dir = opendir(pwd);
	i = -1;
	entry = readdir(dir);
	while (++i, entry)
	{
		files = ft_reallocf(files, i * sizeof(char *),
				(i + 1) * sizeof(char *));
		files[i] = ft_strdup(entry->d_name);
		if (!files || !files[i])
			crash_exit();
		entry = readdir(dir);
	}
	closedir(dir);
	files = ft_reallocf(files, i * sizeof(char *), (i + 1) * sizeof(char *));
	if (!files)
		crash_exit();
	files[i] = 0;
	return (files);
}

int	to_next_wildcard(char *arg, char *str, int *i, int *j)
{
	if (*j == 0 && str[*j] == '*')
		(*i)++;
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
		while (str[*j] && str[*j + 1] && str[*j + 1] == '*')
			(*j)++;
		if (str[*j] == '*')
			return (1);
	}
	return (1);
}

int	is_wildcard(char *arg, char *str)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	if (only_wildcard(str) && arg[0] == '.')
		return (0);
	while (str[j])
	{
		if (!is_last_wildcard(str + j))
			if (!to_next_wildcard(arg, str, &i, &j))
				return (0);
		if (is_last_wildcard(str + j))
		{
			j = ft_strlen(str) + 1;
			i = ft_strlen(arg) + 1;
			while (i >= 0 && arg[--i] == str[--j])
				;
			if (str[j] == '*')
				return (1);
			return (0);
		}
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
		if (is_wildcard(arg[i], str))
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
