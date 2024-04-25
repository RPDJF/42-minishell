/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace_first.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 13:19:49 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/26 00:25:35 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

static void	fill_str(char *src, char *old, char *new, char *output)
{
	char	*tmp;
	size_t	size;

	size = 0;
	tmp = ft_strnstr(src, old, ft_strlen(src));
	ft_strlcpy(output + size, src, tmp - src + 1);
	size += tmp - src;
	src += tmp - src;
	ft_strlcpy(output + size, new, ft_strlen(new) + 1);
	size += ft_strlen(new);
	src += ft_strlen(old);
	ft_strlcpy(output + size, src, tmp - src + 1);
}

char	*ft_strreplace_first(char *src, char *old, char *new)
{
	char	*output;
	size_t	size;

	size = ((ft_strlen(src) + (ft_strlen(new) - ft_strlen(old))) + 1);
	output = galloc(size);
	if (!output)
		return (0);
	fill_str(src, old, new, output);
	return (output);
}
