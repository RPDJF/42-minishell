/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:54:06 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/11 15:12:28 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t				i;
	unsigned char		*tab;

	tab = (unsigned char *)b;
	i = -1;
	while (i++, i != len)
		tab[i] = c;
	return (tab);
}
/*
#include <stdio.h>
int	main()
{
	char tab[] = "bonjour a tous";
	printf("%s", ft_memset(tab, 'P', 4));
}
*/
