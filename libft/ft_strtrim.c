/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 10:42:39 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 16:26:03 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_len(char const *s1, char const *set)
{
	unsigned int	len;

	len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
	{
		len--;
		s1++;
	}
	while (*s1)
		s1++;
	if (len > 0)
		s1--;
	while (*s1 && ft_strchr(set, *s1) && len > 0)
	{
		len--;
		s1--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*arr;
	unsigned int	len;

	if (!s1 || !set)
		return (0);
	len = count_len(s1, set);
	arr = ft_calloc(len + 1, 1);
	if (arr == 0)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	ft_memcpy(arr, s1, len);
	return (arr);
}
