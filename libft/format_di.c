/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:27:32 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:05:33 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	format_di_pre(t_info *info, char *s2, char *s1, int i)
{
	if (!(info->minus == 1 || info->flag_pl == 1 || info->flag_sp == 1))
		s2++;
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
	if (info->flag_pl == 1 || info->flag_sp == 1 || info->minus == 1)
	{
		while (*s1 != '0')
			s1++;
		if (info->minus == 1)
			*s1 = '-';
		else if (info->flag_pl == 1)
			*s1 = '+';
		else if (info->flag_sp == 1)
			*s1 = ' ';
	}
}

void	format_di_nopre(t_info *info, char *s2, char *s1, int size)
{
	if (!(info->minus == 1 || info->flag_pl == 1 || info->flag_sp == 1))
		s2++;
	ft_memset(s1, ' ', size);
	if (info->flag_mi == 1)
		ft_memcpy(s1, s2, info->len + info->add);
	else if (info->flag_ze == 0)
		ft_memcpy(s1 + size - info->len - info->add, s2, info->len + info->add);
	else if (info->flag_ze == 1)
	{
		ft_memcpy(s1 + size - info->len - info->add, s2, info->len + info->add);
		ft_memset(s1, '0', size - info->len - info->add);
	}
	if (info->flag_pl == 1 || info->flag_sp == 1 || info->minus == 1)
	{
		while (*s1 && *s1 != '0')
			s1++;
		if (info->minus == 1)
			*s1 = '-';
		else if (info->flag_pl == 1)
			*s1 = '+';
		else if (info->flag_sp == 1)
			*s1 = ' ';
	}
}

void	format_di_me(t_info *info, char *nbrstr, int size)
{
	char	*str;

	if (info->wid > size)
		size = info->wid;
	str = malloc(size);
	if (str == 0)
	{
		info->ret = -1;
		return ;
	}
	if (nbrstr[0] == '-')
	{
		info->minus = 1;
		nbrstr[0] = '0';
	}
	if (info->pre < 0)
		format_di_nopre(info, nbrstr, str, size);
	else
	{
		if (info->pre < info->len)
			info->pre = info->len;
		format_di_pre(info, nbrstr, str, size);
	}
	ft_write(info, str, size);
	free(str);
}

void	format_di(va_list *ap, t_info *info)
{
	char	*nbrstr;
	int		size;
	int		i;

	i = va_arg(*ap, int);
	if (!i && !info->pre && info->wid < 0 && !info->flag_pl && !info->flag_sp)
		return ;
	nbrstr = ft_itoa(i);
	if (nbrstr == 0)
	{
		info->ret = -1;
		return ;
	}
	if (!(i == 0 && info->pre == 0))
		info->len = ft_strlen(nbrstr) - 1;
	size = info->len;
	if (info->pre > size)
		size = info->pre;
	if (nbrstr[0] == '-' || info->flag_pl == 1 || info->flag_sp == 1)
	{
		size++;
		info->add = 1;
	}
	format_di_me(info, nbrstr, size);
	free(nbrstr);
}
