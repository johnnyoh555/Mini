/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:34:01 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 16:00:10 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start + len > s_len)
	{
		if (start < s_len)
			len = s_len - start;
		else
			len = 0;
	}
	str = ft_calloc(len + 1, 1);
	if (str == 0)
		return (0);
	ft_memcpy(str, s + start, len);
	return (str);
}
