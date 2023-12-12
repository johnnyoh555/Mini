/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_watershed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:42:08 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:05:56 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	watershed(va_list *ap, t_info *info)
{
	if (info->format == 'c')
		format_c(ap, info);
	else if (info->format == 's')
		format_s(ap, info);
	else if (info->format == 'd' || info->format == 'i')
		format_di(ap, info);
	else if (info->format == 'x' || info->format == 'X')
		format_x(ap, info);
	else if (info->format == 'p')
		format_p(ap, info);
	else if (info->format == 'u')
		format_u(ap, info);
	else
		format_else(info);
}

int	check_pre_or_wid(const char **s)
{
	int	i;

	i = ft_atoi(*s);
	while (**s >= '0' && **s <= '9')
		(*s)++;
	return (i);
}

void	check_flag(const char **s, t_info *info)
{
	if (**s == ' ')
	{
		info->flag_sp = 1;
		(*s)++;
	}
	if (**s == '0')
	{
		info->flag_ze = 1;
		(*s)++;
	}
	if (**s == '-')
	{
		info->flag_mi = 1;
		(*s)++;
	}
	if (**s == '+')
	{
		info->flag_pl = 1;
		(*s)++;
	}
	if (**s == '#')
	{
		info->flag_sh = 1;
		(*s)++;
	}
}

void	if_percent(const char **s, va_list *ap, t_info *info)
{
	char	*c;

	(*s)++;
	c = 0;
	while (*s != c)
	{
		c = (char *)*s;
		check_flag(s, info);
		if (**s == '.')
		{
			(*s)++;
			if (**s < '0' || **s > '9')
				info->pre = 0;
			else
				info->pre = check_pre_or_wid(s);
		}
		if (**s >= '1' && **s <= '9')
			info->wid = check_pre_or_wid(s);
	}
	if (!(**s))
		return ;
	info->format = **s;
	(*s)++;
	watershed(ap, info);
}
