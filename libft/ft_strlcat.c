/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:53:10 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 15:03:04 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t	dlen;
	size_t	slen;

	if (dst == 0 && destsize == 0)
		return (0);
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (destsize <= dlen)
		return (slen + destsize);
	ft_strlcpy(dst + dlen, src, destsize - dlen);
	return (slen + dlen);
}
