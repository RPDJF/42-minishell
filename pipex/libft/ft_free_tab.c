/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:51:42 by ilyanar           #+#    #+#             */
/*   Updated: 2024/01/29 21:19:26 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (1);
	while (*(tab + i))
		i++;
	while (i >= 0)
	{
		free(*(tab + i));
		i--;
	}
	free(tab);
	return (0);
}
