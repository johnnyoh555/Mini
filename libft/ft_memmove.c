/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:11:21 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 13:12:53 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cpy_dest;
	unsigned char	*cpy_src;

	cpy_dest = (unsigned char *)dst;
	cpy_src = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	if (cpy_src < cpy_dest)
	{
		while (len-- > 0)
			cpy_dest[len] = cpy_src[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
