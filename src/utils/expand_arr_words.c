#include "expand_words.h"

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

int	is_wildcard(char *arg, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (arg[++i] == str[++j])
		;
	if (str[j] == '*')
	{
		j = ft_strlen(str) + 1;
		i = ft_strlen(arg) + 1;
		while (i >= 0 && arg[--i] == str[--j])
			;
		if (str[j] == '*')
			return (1);
	}
	return (0);
}

char	**pars_wildcard(char *str)
{
	char	**arg;
	char	**tmp;
	int		i;

	i = 2;
	tmp = NULL;
	arg = get_files();
	while (arg[i])
	{
		if (is_wildcard(arg[i], str) && arg[i][0] != '.')
			tmp = strr_realloc(tmp, arg[i]);
		i++;
	}
	ft_free_tab(arg);
	return (tmp);
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
	while (arr[0][*i])
		*i += 1;
}

char	**parse_words_arr(t_word **words)
{
	char	**arr;
	char	**wld;
	size_t	count;
	size_t	i;

	count = words_arr_len(words);
	arr = galloc(sizeof(char *) * (count + 1));
	if (!arr)
		crash_exit();
	count = 0;
	i = -1;
	while (i++, words[count])
	{
		arr[i] = parse_words(words[count]);
		if (ft_strchr(arr[i], '*'))
		{
			wld = pars_wildcard(arr[i]);
			if (wld)
				realloc_arr(&arr, wld, &i);
		}
		count++;
	}
	arr[i] = 0;
	return (arr);
}
