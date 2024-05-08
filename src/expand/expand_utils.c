#include "expand_words.h"

size_t	words_arr_len(t_word **words)
{
	size_t	len;

	len = 0;
	while (words[len])
		len++;
	return (len);
}

size_t	words_strlen(t_word *words)
{
	size_t	len;

	len = 1;
	while (words)
	{
		len += ft_strlen(words->str);
		words = words->next;
	}
	return (len);
}
