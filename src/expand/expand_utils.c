/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:51 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:25:53 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
