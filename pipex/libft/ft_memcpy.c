/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:32:13 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/18 01:45:36 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (const char *)src;
	i = -1;
	if (!dst && !src)
		return (NULL);
	while (i++, i != n)
		d[i] = s[i];
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("M_test : %s\n", (char *)ft_memcpy(((void *)0)
}
*/
