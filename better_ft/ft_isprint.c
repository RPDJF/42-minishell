/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:54:40 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/10 17:32:50 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	printf("%d\n", ft_isprint('c'));
	printf("%d\n", ft_isprint(30));
	printf("%d\n", ft_isprint(67));
}
*/
