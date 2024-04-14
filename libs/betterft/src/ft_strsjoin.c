/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:23:41 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/14 16:14:09 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_strsjoin(size_t size, ...)
{
	bool	trigger;
	va_list	va;
	char	*output;
	char	*swap;
	size_t	i;

	trigger = false;
	va_start(va, size);
	output = 0;
	i = 0;
	while (i++ < size)
	{
		swap = output;
		if (trigger)
			output = ft_strjoin(output, va_arg(va, char *));
		else
			output = va_arg(va, char *);
		if (!output)
			return (0);
		trigger = true;
		if (i > 2)
			gfree(swap);
	}
	va_end(va);
	return (output);
}
