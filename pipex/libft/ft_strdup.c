/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:34:58 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/19 18:53:31 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tab;

	tab = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!tab)
		return (0);
	ft_memcpy(tab, s, ft_strlen(s));
	return (tab);
}
/*
#include <stdio.h>
int	main()
{
	char tab[] = "hello";

	printf("%s\n", ft_strdup(tab));
}
*/
