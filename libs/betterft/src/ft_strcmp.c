/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:02:51 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 14:18:34 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "../betterft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main(void)
{
	ft_printf("%d\n", ft_strcmp("ok", "ok"));
	ft_printf("%d\n", ft_strcmp("nok", "ok"));
	ft_printf("%d\n", ft_strcmp("ok", "nok"));
	ft_printf("%d\n", ft_strcmp("nok", 0));
	ft_printf("%d\n", ft_strcmp(0, "nok"));
	ft_printf("%d\n", ft_strcmp(0, 0));
}