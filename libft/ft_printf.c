/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:53:43 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:02:35 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_info(t_info *info)
{
	info->flag_ze = 0;
	info->flag_mi = 0;
	info->flag_pl = 0;
	info->flag_sh = 0;
	info->flag_sp = 0;
	info->wid = -100;
	info->pre = -100;
	info->minus = 0;
	info->add = 0;
	info->len = 0;
}

int	while_str(const char **s, t_info *info)
{
	int	i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '%')
		i++;
	if (write(1, *s, i) < 0)
		return (1);
	*s += i;
	info->ret += i;
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	t_info	info;

	va_start(ap, s);
	info.ret = 0;
	while (*s)
	{
		reset_info(&info);
		if (while_str(&s, &info))
		{
			info.ret = -1;
			break ;
		}
		if (*s == '%')
			if_percent(&s, &ap, &info);
		if (info.ret == -1)
			break ;
	}
	va_end(ap);
	return (info.ret);
}
