/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 00:33:21 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/20 03:33:30 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	ft_memcpy(s3, s1, ft_strlen(s1));
	ft_memcpy((s3 + ft_strlen(s1)), s2, ft_strlen(s2));
	return (s3);
}
/*
#include <stdio.h>
int	main()
{
	
	char tab[] = "hello";
	//char tab2[] = " a tous";
	printf("%s", ft_strjoin(tab, tab));
}
*/
