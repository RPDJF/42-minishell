/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 04:45:25 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/20 16:22:18 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			nb++;
		}
	}
	return (nb);
}

static size_t	ft_lenc(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i + 1);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	char	**tab;

	j = ft_count_words(s, c);
	tab = ft_calloc(j + 1, sizeof(char **));
	if (!tab)
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			tab[j] = ft_calloc(ft_lenc(s, c), sizeof(char));
			if (!tab[j])
				return (ft_free(tab));
			ft_memcpy(tab[j], s, ft_lenc(s, c) - 1);
			j++;
			while (*s != c && *s != '\0')
				s++;
		}
	}
	return (tab);
}
/*
#include <unistd.h>
int	main()
{
	char tab[] = "lorem ips Sed non risus. Suspendisse";
	char c = ' ';
	ft_split(tab, c);
}
*/
