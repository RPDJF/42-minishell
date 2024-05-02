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

int	to_next_wildcard(char *arg, char *str, int *i, int *j)
{
	if (str[*j] == '*')
	{
		while (str[*j] == '*')
			*j += 1;
		while (arg[*i] && arg[*i] != str[*j])
			*i += 1;
	}
	else if (*i > 0)
		while (arg[*i] && arg[*i] != str[*j])
			*i += 1;
	if (arg[*i] != str[*j] || !arg[*i])
		return (0);
	while (arg[*i] && str[*j] && arg[*i] == str[*j])
	{
		*i += 1;
		*j += 1;
		if (str[*j] == '*')
			return (1);
	}
	return (1);
}

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

int	is_wildcard(char *arg, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (!is_last_wildcard(str + j))
		{
			if (!to_next_wildcard(arg, str, &i, &j))
				return (0);
		}
		else if (is_last_wildcard(str + j))
		{
			j = ft_strlen(str) + 1;
			i = ft_strlen(arg) + 1;
			while (i >= 0 && arg[--i] == str[--j])
				;
			if (str[j] == '*')
				return (1);
			else
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

	i = 2;
	tmp = NULL;
	arg = get_files();
	while (arg[i])
	{
		if (is_wildcard(arg[i], str))
		{
			if (str[0] == '*' && !str[1] && arg[i][0] == '.' && i++)
				continue ;
			tmp = strr_realloc(tmp, arg[i]);
		}
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
	while (arr[0][*i + 1])
		*i += 1;
}

char	**wildcard_quoted(t_word *cmd)
{
	char	**is_quoted;

	is_quoted = NULL;
	while (cmd)
	{
		if (cmd->is_quoted == true)
			is_quoted = strr_realloc(is_quoted, "1");
		if (cmd->is_quoted == false)
			is_quoted = strr_realloc(is_quoted, "0");
		cmd = cmd->next;
	}
	return (is_quoted);
}

char	**parse_words_arr(t_word **words)
{
	char	**arr;
	char	**wld;
	char	**is_quoted;
	size_t	j;
	size_t	i;

	arr = NULL;
	j = -1;
	i = -1;
	while (i++, words[++j])
	{
		is_quoted = wildcard_quoted(words[j]);
		arr = strr_realloc(arr, parse_words(words[j]));
		if (ft_strchr(arr[i], '*'))
		{
			wld = pars_wildcard(arr[i]);
			if (wld)
				realloc_arr(&arr, wld, &i);
		}
		if (is_quoted && *is_quoted)
			ft_free_tab(is_quoted);
	}
	return (arr);
}
