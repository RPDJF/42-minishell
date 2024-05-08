/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:47 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:25:49 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (!words)
		return (0);
	head = galloc(sizeof(t_word *) * 2);
	head[0] = words;
	head[1] = 0;
	arr = parse_words_arr(head);
	str = ft_strsepjoin(arr, 28);
	ft_free_tab(arr);
	gfree(head);
	return (str);
}

char	*parse_words(t_word *words)
{
	char	*output;
	t_word	*head;
	size_t	len;
	char	*tmp;

	words = expand_words(words);
	if (!words)
		return (0);
	head = words;
	len = words_strlen(words);
	output = ft_calloc(len, sizeof(char));
	if (!output)
		crash_exit();
	while (head)
	{
		tmp = output;
		output = ft_strjoin(output, head->str);
		if (!output)
			crash_exit();
		if (*tmp)
			gfree(tmp);
		head = head->next;
	}
	return (output);
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
