/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_u_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:01:49 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:05:02 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	format_u_pre(t_info *info, char *nbrstr, char *str, int size)
{
	nbrstr++;
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
}

void	format_u_nopre(t_info *info, char *nbrstr, char *str, int size)
{
	nbrstr++;
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
}

void	format_u_me(t_info *info, char *nbrstr, int size)
{
	char	*str;

	str = malloc(size);
	if (str == 0)
	{
		info->ret = -1;
		return ;
	}
	if (info->pre < 0)
		format_u_nopre(info, nbrstr, str, size);
	else
	{
		if (info->pre < info->len)
			info->pre = info->len;
		format_u_pre(info, nbrstr, str, size);
	}
	ft_write(info, str, size);
	free(str);
}

void	format_u(va_list *ap, t_info *info)
{
	char			*nbrstr;
	int				size;
	unsigned int	i;

	i = (unsigned int)va_arg(*ap, int);
	if (!i && !info->pre && info->wid < 0)
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
	if (info->wid > size)
		size = info->wid;
	format_u_me(info, nbrstr, size);
	free(nbrstr);
}
