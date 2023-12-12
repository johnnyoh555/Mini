/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:02:11 by jooh              #+#    #+#             */
/*   Updated: 2023/10/20 10:26:46 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cpy_dest;
	unsigned char	*cpy_src;
	size_t			i;

	i = 0;
	cpy_dest = (unsigned char *)dst;
	cpy_src = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		cpy_dest[i] = cpy_src[i];
		i++;
	}
	return (dst);
}
