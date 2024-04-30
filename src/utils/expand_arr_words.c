#include "expand_words.h"

char	**pars_wildcard(char *str)
{
	char	**arg;

	arg = 0; 
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
