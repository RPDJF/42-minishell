/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_un.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:03:30 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_itoa_un(unsigned long n)
{
	char			*p;
	unsigned int	temp;
	int				len;

	temp = n;
	len = 0;
	while (++len, temp >= 10)
		temp /= 10;
	p = (char *)ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (0);
	temp = n;
	while (len-- > 0)
	{
		p[len] = (temp % 10) + '0';
		temp /= 10;
	}
	return (p);
}
