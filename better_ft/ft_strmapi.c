/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 00:11:54 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/21 12:37:12 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*tab;

	i = -1;
	if (!s || !f)
		return (NULL);
	tab = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (i++, s[i])
		tab[i] = (*f)(i, s[i]);
	tab[i] = '\0';
	return (tab);
}
