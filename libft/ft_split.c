/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:19:29 by jooh              #+#    #+#             */
/*   Updated: 2023/11/20 22:17:07 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static int	countsize(char const *s, char c)
{
	int	size;
	int	i;

	size = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = str_len(s, c);
		s += i;
		if (i)
			size++;
	}
	return (size);
}

static char	*str_cpy(char const *s, int j)
{
	char	*arr2;

	arr2 = ft_calloc((j + 1), 1);
	if (arr2 == 0)
		return (0);
	ft_memcpy(arr2, s, j);
	return (arr2);
}

static void	ft_free(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		size;
	int		i;

	if (s == 0)
		return (0);
	size = countsize(s, c);
	arr = (char **)ft_calloc(size + 1, sizeof(char *));
	if (arr == 0)
		return (0);
	i = -1;
	while (++i < size)
	{
		while (*s && *s == c)
			s++;
		arr[i] = str_cpy(s, str_len(s, c));
		if (arr[i] == 0)
		{
			ft_free(arr, i);
			return (0);
		}
		s += str_len(s, c);
	}
	return (arr);
}
