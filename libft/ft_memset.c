/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:22:24 by jooh              #+#    #+#             */
/*   Updated: 2023/10/08 11:08:56 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	change_data;
	unsigned char	*ret_string;
	size_t			i;

	i = 0;
	change_data = (unsigned char)c;
	ret_string = (unsigned char *)b;
	while (i < len)
	{
		ret_string[i] = change_data;
		i++;
	}
	return (b);
}
