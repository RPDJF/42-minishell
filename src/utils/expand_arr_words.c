#include "expand_words.h"

char	**pars_wildcard(char *str)
{
	char	**arg;

	arg = 0;
}

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
	i = -1;
	while (i++, words[i])
	{
		arr[i] = parse_words(words[i]);
		if (ft_strchr(arr[i], '*'))
			wld = pars_wildcard(arr[i]);
	}
	arr[i] = 0;
	return (arr);
}
