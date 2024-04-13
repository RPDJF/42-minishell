/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joint_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:23:27 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/13 23:24:06 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_joint_all(char **str)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 1;
	if (!str)
		return (NULL);
	if (str && str[0])
		tmp1 = ft_strdup(str[0]);
	while (str[i])
	{
		tmp2 = ft_strjoin(tmp1, str[i]);
		gfree(tmp1);
		i++;
		if (!str[i])
			return (tmp2);
		tmp1 = ft_strjoin(tmp2, str[i]);
		gfree(tmp2);
		i++;
		if (!str[i])
			return (tmp1);
	}
	return (tmp1);
}
