/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:22:15 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/18 19:37:38 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (s < d && d < s + len)
	{
		while (len--)
			d[len] = s[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char tab[30] = "eeeeeipsum dolor sit a";
	char src[] = "consectetur";

	ft_memmove(tab, src, 5);
	//memmove(tab, "hello", 0);
	printf("%s", tab);
}
*/
