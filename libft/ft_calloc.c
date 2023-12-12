/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:59:27 by jooh              #+#    #+#             */
/*   Updated: 2023/12/11 21:21:07 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	i;

	if (!count || !size)
		return (malloc(0));
	if (size > -1 / count)
		return (0);
	i = count * size;
	arr = malloc(sizeof(char) * i);
	if (arr == 0)
		err_seq("malloc", 0, 1, 0);
	ft_bzero(arr, i);
	return (arr);
}
