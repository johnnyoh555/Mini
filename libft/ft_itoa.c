/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:40:55 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 11:12:36 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	trans(int long n, char *arr, int j)
{	
	int	i;

	if (n)
	{
		trans(n / 10, arr, j - 1);
		i = n % 10;
		arr[j - 1] = '0' + i;
	}
}

static void	to_char(int long n, char *arr, int j)
{
	if (n == 0)
	{
		arr[0] = '0';
		return ;
	}
	else if (n < 0)
	{
		n *= -1;
		arr[0] = '-';
		trans(n, arr, j);
	}
	else
		trans(n, arr, j);
}

static int	how_much(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		size;

	size = how_much(n);
	if (n > 0)
		arr = ft_calloc(size + 1, 1);
	else
		arr = ft_calloc(size + 2, 1);
	if (arr == 0)
		return (0);
	if (n < 0)
		to_char((int long)n, arr, size + 1);
	else
		to_char((int long)n, arr, size);
	return (arr);
}
