/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:37:20 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 14:30:49 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dstsize)
	{
		if (len < dstsize)
			ft_memcpy(dst, src, len + 1);
		else
		{
			ft_memcpy(dst, src, dstsize - 1);
			*(dst + dstsize - 1) = 0;
		}
	}
	return (len);
}
