/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:44:49 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/11 13:08:56 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*tab;

	i = 0;
	tab = (char *)s;
	while (i != n)
	{
		tab[i] = '\0';
		i++;
	}
}
/*
int	main()
{
	char tab[] = "hello";
	ft_bzero(tab, 3);
}
*/
