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

char	**get_files(void)
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
