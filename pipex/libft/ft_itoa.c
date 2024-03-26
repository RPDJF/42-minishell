/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:23:44 by ilyanar           #+#    #+#             */
/*   Updated: 2023/11/22 17:55:53 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_negnb(char *tab, int *n, int *i)
{
	if (*n == -2147483648)
	{
		*i = 0;
		tab[*i] = '8';
		*n = *n / 10;
	}
	*n = *n * -1;
}

char	*ft_itoa(int n)
{
	int		i;
	int		nb;
	char	*tab;

	i = -1;
	nb = n;
	tab = ft_calloc(ft_size(nb) + 1, sizeof(char));
	if (!tab)
		return (NULL);
	if (n < 0)
		ft_negnb(tab, &n, &i);
	if (n == 0)
		tab[0] = '0';
	while (i++, n > 0)
	{
		if (n > 9)
			tab[i] = (n % 10) + 48;
		else if (n >= 0 && n <= 9)
			tab[i] = n + 48;
		n = n / 10;
	}
	if (nb < 0)
		tab[i] = '-';
	ft_rev_tab(tab);
	return (tab);
}
/*
#include <stdio.h>
int	main(void)
{
	int	i;

	i = -2147483648;
	printf("%s", ft_itoa(i));
}
*/
