/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:29:27 by jooh              #+#    #+#             */
/*   Updated: 2023/10/07 15:55:50 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_nbr(int long value, int fd)
{
	char	c;

	if (value)
	{
		write_nbr(value / 10, fd);
		c = value % 10 + '0';
		write (fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int long	value;

	value = n;
	if (value == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	if (value < 0)
	{
		write (fd, "-", 1);
		value *= -1;
	}
	write_nbr (value, fd);
}
