/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:57:14 by ilyanar           #+#    #+#             */
/*   Updated: 2024/01/19 19:56:55 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	s3 = (char *)gnl_calloc(gnl_strlen(s1) + gnl_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	gnl_memcpy(s3, s1, gnl_strlen(s1));
	gnl_memcpy((s3 + gnl_strlen(s1)), s2, gnl_strlen(s2));
	free((char *)s1);
	return (s3);
}

void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (const char *)src;
	i = -1;
	if (!dst && !src)
		return (NULL);
	while (i++, i != n)
		d[i] = s[i];
	return (dst);
}

void	*gnl_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	i;

	i = -1;
	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	while (i++, i < count * size)
		((char *)tab)[i] = '\0';
	return (tab);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if (!(unsigned char)c)
		return ((char *)s + gnl_strlen(s));
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == '\0')
		return (0);
	return ((char *)s);
}
