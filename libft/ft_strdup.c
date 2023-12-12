/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:19:35 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 12:09:04 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*arr;
	size_t		s_len;

	s_len = ft_strlen(s1);
	arr = ft_calloc(s_len + 1, 1);
	if (arr == 0)
		return (0);
	ft_memcpy(arr, s1, s_len);
	return (arr);
}
