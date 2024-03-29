/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:01:00 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

void	ft_putnbr_base(int n, char *base, int fd)
{
	unsigned int	un;
	size_t			baselen;

	un = n;
	if (n < 0)
		un = -n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	baselen = ft_strlen(base);
	if (un < baselen)
		ft_putchar_fd(base[un], fd);
	else if (un > baselen)
	{
		ft_putnbr_base(un / baselen, base, fd);
		ft_putnbr_base(un % baselen, base, fd);
	}
}
