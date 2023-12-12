/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:28:29 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:04:08 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	trans(long n, char *arr, int j)
{	
	int	i;

	if (n)
	{
		trans(n / 10, arr, j - 1);
		i = n % 10;
		arr[j - 1] = '0' + i;
	}
}

static void	to_char(long n, char *arr, int j)
{
	if (n == 0)
	{
		arr[0] = '0';
		arr[1] = '0';
		arr[2] = 0;
		return ;
	}
	else if (n < 0)
	{
		n *= -1;
		arr[0] = '-';
		trans(n, arr, j);
	}
	else
	{
		arr[0] = '0';
		trans(n, arr, j);
	}
	arr[j] = 0;
}

char	*ft_itoa(long n)
{
	char	*arr;
	int		size;
	long	i;

	i = n;
	size = 0;
	while (i)
	{
		i /= 10;
		size++;
	}
	if (n == 0)
		size++;
	arr = malloc(size + 2);
	if (arr == 0)
		return (0);
	to_char(n, arr, size + 1);
	return (arr);
}
