/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:05:02 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:04:31 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	trans(unsigned long long n, char *arr, unsigned int j, char *base)
{	
	unsigned int	i;

	if (n)
	{
		trans(n / 16, arr, j - 1, base);
		i = n % 16;
		arr[j - 1] = base[i];
	}
}

static void	to_char(unsigned long long n, char *arr, unsigned int j, char *base)
{
	arr[0] = '0';
	arr[1] = '0';
	if (n == 0)
	{
		arr[2] = '0';
		arr[3] = 0;
		return ;
	}
	else
		trans(n, arr, j, base);
	arr[j] = 0;
}

char	*ft_convert(unsigned long long n, char *base)
{
	char				*arr;
	unsigned int		size;
	unsigned long long	i;

	i = n;
	size = 0;
	while (i)
	{
		i /= 16;
		size++;
	}
	if (n == 0)
		size++;
	arr = malloc(size + 3);
	if (arr == 0)
		return (0);
	to_char(n, arr, size + 2, base);
	return (arr);
}
