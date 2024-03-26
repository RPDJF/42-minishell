/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 00:49:08 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/20 04:14:04 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != 0)
		++s1;
	if (*s1 == 0)
		return (s2 = (char *)ft_calloc(1, 1));
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i--;
	s2 = (char *)ft_calloc(i + 2, sizeof(char));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, i + 1);
	return (s2);
}
/*
#include <stdio.h>
int	main()
{
	char tab[] = "pprrphelloprprp";
	char set[] = "pr";

	printf("%s", ft_strtrim(tab, set));
}
*/
