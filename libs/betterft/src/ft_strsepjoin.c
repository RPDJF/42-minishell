/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsepjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:51:13 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 01:53:24 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_strsepjoin(char **arr, char sep)
{
	char	*output;
	char	*tmp;

	output = 0;
	while (*arr)
	{
		tmp = output;
		output = ft_strjoin(output, *arr);
		if (!output)
			return (0);
		if (tmp)
			gfree(tmp);
		if (*(arr + 1))
		{
			tmp = output;
			output = ft_strjoin(output, (char []){sep, 0});
			if (!output)
				return (0);
			gfree(tmp);
		}
		arr++;
	}
	return (output);
}
