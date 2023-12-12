/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:49:48 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:05:22 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	format_p_pre(t_info *info, char *nbrstr, char *str, int size)
{
	if (info->flag_mi == 1)
	{
		ft_memset(str, '0', info->pre - info->len);
		ft_memcpy(str + info->pre - info->len, nbrstr, info->len);
		ft_memset(str + info->pre, ' ', size - info->pre);
	}
	else
	{
		ft_memset(str, ' ', size - info->pre);
		ft_memset(str + size - info->pre, '0', info->pre - info->len);
		ft_memcpy(str + size - info->len, nbrstr, info->len);
	}
	while (*str != '0')
		str++;
	str[0] = '0';
	str[1] = 'x';
}

void	format_p_nopre(t_info *info, char *nbrstr, char *str, int size)
{
	ft_memset(str, ' ', size);
	if (info->flag_mi == 1)
		ft_memcpy(str, nbrstr, info->len);
	else if (info->flag_ze == 0)
		ft_memcpy(str + size - info->len, nbrstr, info->len);
	else if (info->flag_ze == 1)
	{
		ft_memcpy(str + size - info->len, nbrstr, info->len);
		ft_memset(str, '0', size - info->len);
	}
	while (*str != '0')
		str++;
	str[0] = '0';
	str[1] = 'x';
}

void	format_p_me(t_info *info, char *nbrstr, int size)
{
	char	*str;

	str = malloc(size);
	if (str == 0)
	{
		info->ret = -1;
		return ;
	}
	if (info->pre < 0)
		format_p_nopre(info, nbrstr, str, size);
	else
	{
		if (info->pre < info->len)
			info->pre = info->len;
		format_p_pre(info, nbrstr, str, size);
	}
	ft_write(info, str, size);
	free(str);
}

void	format_p(va_list *ap, t_info *info)
{
	char		*nbrstr;
	int			size;
	long long	i;

	i = va_arg(*ap, unsigned long);
	nbrstr = ft_convert(i, "0123456789abcdef");
	if (nbrstr == 0)
	{
		info->ret = -1;
		return ;
	}
	if (i == 0 && info->pre == 0)
		info->len = 2;
	else
		info->len = ft_strlen(nbrstr);
	size = info->len;
	info->pre += 2;
	if (info->pre > size)
		size = info->pre;
	if (info->wid > size)
		size = info->wid;
	format_p_me(info, nbrstr, size);
	free(nbrstr);
}
