/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:07:50 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 15:15:28 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	if (haystack == 0 && len == 0)
		return (0);
	needle_len = (ft_strlen(needle));
	if ((haystack && needle_len - 1 >= len) || *haystack == 0)
		return (0);
	while (i < len - (needle_len - 1) || haystack == 0)
	{
		if (*haystack == *needle)
		{
			if (!ft_strncmp(haystack, needle, needle_len))
				return ((char *)haystack);
		}
		haystack++;
		i++;
	}
	return (0);
}
