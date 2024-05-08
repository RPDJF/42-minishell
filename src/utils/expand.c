#include "expand_words.h"

char	*join_words(t_word *words)
{
	char	*output;
	char	*tmp;

	output = 0;
	while (words)
	{
		tmp = output;
		output = ft_strjoin(output, words->str);
		if (!output)
			crash_exit();
		if (tmp)
			gfree(tmp);
		words = words->next;
	}
	return (output);
}

char	*parse_words_line(t_word *words)
{
	t_word	**head;
	char	**arr;
	char	*str;

	head = galloc(sizeof(t_word *) * 2);
	head[0] = words;
	head[1] = 0;
	arr = parse_words_arr(head);
	str = ft_strsepjoin(arr, 28);
	ft_free_tab(arr);
	gfree(head);
	return (str);
}
