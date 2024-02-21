/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 07:42:45 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	last;

	if (!(unsigned char)c)
		return ((char *)s + ft_strlen(s));
	i = 1;
	last = 0;
	while (s[i - 1])
	{
		if (s[i - 1] == (unsigned char)c)
			last = i;
		i++;
	}
	if (!last)
		return (0);
	return ((char *)s + last - 1);
}
