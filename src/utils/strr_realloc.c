/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strr_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:05:48 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/04 17:16:07 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// Realloc and return a char ** from str and add the char *neww to the end
char	**strr_realloc(char **str, char *neww)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str)
		while (str[i] != NULL)
			i++;
	tab = ft_calloc(i + 2, sizeof(char *));
	while (i > 0 && j < i)
	{
		tab[j] = ft_strdup(str[j]);
		j++;
	}
	tab[j] = ft_strdup(neww);
	if (str && *str)
		ft_free_tab(str);
	return (tab);
}
