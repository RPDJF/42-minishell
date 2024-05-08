/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strr_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:30:35 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:30:37 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_handler.h"

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
	if (!tab)
		crash_exit();
	while (i > 0 && j < i)
	{
		tab[j] = str[j];
		j++;
	}
	tab[j] = ft_strdup(neww);
	if (!tab[j])
		crash_exit();
	gfree(str);
	return (tab);
}
