/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:53:11 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:10:48 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	format_x_pre(t_info *info, char *s2, char *s1, int i)
{
	if (info->flag_sh == 0)
		s2 += 2;
	if (info->flag_mi == 1)
	{
		ft_memset(s1, '0', info->pre - info->len);
		ft_memcpy(s1 + info->pre - info->len, s2, info->len + info->add);
		ft_memset(s1 + info->pre + info->add, ' ', i - info->pre - info->add);
	}
	else
	{
		ft_memset(s1, ' ', i - info->pre - info->add);
		ft_memset(s1 + i - info->pre - info->add, '0', info->pre - info->len);
		ft_memcpy(s1 + i - info->len - info->add, s2, info->len + info->add);
	}
	if (info->flag_sh == 1)
	{
		while (*s1 != '0')
			s1++;
		s1[0] = '0';
		if (info->format == 'x')
			s1[1] = 'x';
		else if (info->format == 'X')
			s1[1] = 'X';
	}
}

void	format_x_nopre(t_info *info, char *s2, char *s1, int i)
{
	if (info->flag_sh == 0)
		s2 += 2;
	ft_memset(s1, ' ', i);
	if (info->flag_mi == 1)
		ft_memcpy(s1, s2, info->len + info->add);
	else if (info->flag_ze == 0)
		ft_memcpy(s1 + i - info->len - info->add, s2, info->len + info->add);
	else if (info->flag_ze == 1)
	{
		ft_memcpy(s1 + i - info->len - info->add, s2, info->len + info->add);
		ft_memset(s1, '0', i - info->len - info->add);
	}
	if (info->flag_sh == 1)
	{
		while (*s1 != '0')
			s1++;
		s1[0] = '0';
		if (info->format == 'x')
			s1[1] = 'x';
		else if (info->format == 'X')
			s1[1] = 'X';
	}
}

void	format_x_me(t_info *info, char *nbrstr, int size)
{
	char	*str;

	if (info->flag_sh == 1)
	{
		size += 2;
		info->add = 2;
	}
	if (info->wid > size)
		size = info->wid;
	str = malloc(size);
	if (str == 0)
	{
		info->ret = -1;
		return ;
	}
	if (info->pre < 0)
		format_x_nopre(info, nbrstr, str, size);
	else
	{
		if (info->pre < info->len)
			info->pre = info->len;
		format_x_pre(info, nbrstr, str, size);
	}
	ft_write(info, str, size);
	free(str);
}

void	format_x(va_list *ap, t_info *info)
{
	char			*nbrstr;
	int				size;
	unsigned int	i;

	i = va_arg(*ap, unsigned int);
	if (!i && !info->pre && info->wid < 0 && !info->flag_sh)
		return ;
	if (info->format == 'x')
		nbrstr = ft_convert(i, "0123456789abcdef");
	else
		nbrstr = ft_convert(i, "0123456789ABCDEF");
	if (nbrstr == 0)
	{
		info->ret = -1;
		return ;
	}
	if (!(i == 0 && info->pre == 0))
		info->len = ft_strlen(nbrstr) - 2;
	size = info->len;
	if (info->pre > size)
		size = info->pre;
	if (i == 0)
		info->flag_sh = 0;
	format_x_me(info, nbrstr, size);
	free(nbrstr);
}
