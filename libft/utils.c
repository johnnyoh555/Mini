/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:26:06 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:01:53 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

int	ft_atoi(const char *str)
{
	int			minus;
	int long	value;

	value = 0;
	minus = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		value += *str - '0';
		str++;
	}
	return ((int)(value * minus));
}

void	ft_write(t_info *info, char *str, int len)
{
	if (write(1, str, len) < 0)
	{
		info->ret = -1;
		return ;
	}
	info->ret += len;
}
