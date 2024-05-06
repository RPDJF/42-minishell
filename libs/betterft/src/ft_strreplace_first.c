/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace_first.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 13:19:49 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/06 15:41:44 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

static void	fill_str(char *src, char *old, char *new, char *output)
{
	char	*needle;
	size_t	size;

	size = ft_strlen(src) - ft_strlen(old) + ft_strlen(new) + 1;
	needle = ft_strnstr(src, old, ft_strlen(src));
	ft_strlcpy(output, src, needle - src + 1);
	ft_strlcat(output, new, size);
	ft_strlcat(output, needle + ft_strlen(old), size);
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
