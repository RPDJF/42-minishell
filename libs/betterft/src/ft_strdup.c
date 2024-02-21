/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:37:35 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_strdup(const char *src)
{
	char	*p_galloc;
	int		i;

	p_galloc = (char *)ft_calloc(ft_strlen(src) + 1, sizeof(char));
	if (!p_galloc)
		return (0);
	i = 0;
	while (src[i++])
		p_galloc[i - 1] = src[i - 1];
	return (p_galloc);
}
