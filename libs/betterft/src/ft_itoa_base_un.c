/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_un.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:09:26 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_itoa_base_un(unsigned long n, const char *base)
{
	char				*p;
	unsigned long int	temp;
	size_t				len;

	temp = n;
	len = 0;
	while (++len, temp >= ft_strlen(base))
		temp /= ft_strlen(base);
	p = (char *)ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (0);
	temp = n;
	while (len-- > 0)
	{
		p[len] = base[temp % ft_strlen(base)];
		temp /= ft_strlen(base);
	}
	return (p);
}
