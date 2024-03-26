/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:39:22 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/18 16:44:01 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;

	i = 0;
	while ((i < n))
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};

	printf("M_fonction : %d\n", (char *)ft_memchr(s, 2 + 256, 3) == s + 2);
	printf("V_fonction : %d\n", (char *)memchr(s, 2 + 256, 3) == s + 2);
}
*/
