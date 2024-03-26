/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:57:45 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/20 03:33:09 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;

	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tab = (char *)ft_calloc((len + 1), sizeof(char));
	if (!tab)
		return (NULL);
	ft_memcpy(tab, (s + start), len);
	return (tab);
}
/*
#include <stdio.h>
int	main()
{
	char	tab[] = "FULL DAWDSAWDS";
	printf("%s", ft_substr(tab, 400, 20));
}
*/
