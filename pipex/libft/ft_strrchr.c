/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:40:53 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/18 13:02:35 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = NULL;
	if (!(unsigned char)c)
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (unsigned char)c)
			p = (char *)s;
		s++;
	}
	if (*s == '\0' && p == NULL)
		return (0);
	return (p);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char *tab = "electric_alloc";

	printf("M_FONCTION : %s\n", ft_strrchr(tab, 10));
	printf("V_FONCTION : %s\n", strrchr(tab, 10));
}
*/
