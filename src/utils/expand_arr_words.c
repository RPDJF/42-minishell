#include "expand_words.h"

static size_t	words_arr_len(t_word **words)
{
	size_t	len;

	len = 0;
	while (words[len])
		len++;
	return (len);
}

char	**parse_words_arr(t_word **words)
{
	char	**arr;
	size_t	count;
	size_t	i;

	count = words_arr_len(words);
	arr = galloc(sizeof(char *) * (count + 1));
	if (!arr)
		crash_exit();
	i = -1;
	while (i++, words[i])
		arr[i] = parse_words(words[i]);
	arr[i] = 0;
	return (arr);
}
