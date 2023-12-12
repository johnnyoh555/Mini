/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:24:52 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:05:44 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_format_s(char *str, t_info *info, int len)
{
	char	*put_str;

	put_str = malloc(info->wid);
	if (put_str == 0)
	{
		info->ret = -1;
		return ;
	}
	if (info->flag_mi == 1)
	{
		ft_memset(put_str, ' ', info->wid);
		ft_memcpy(put_str, str, len);
	}
	else if (info->flag_mi == 0 && info->flag_ze == 1)
	{
		ft_memset(put_str, '0', info->wid - len);
		ft_memcpy(put_str + info->wid - len, str, len);
	}
	else if (info->flag_mi == 0 && info->flag_ze == 0)
	{
		ft_memset(put_str, ' ', info->wid - len);
		ft_memcpy(put_str + info->wid - len, str, len);
	}
	ft_write(info, put_str, info->wid);
	free(put_str);
}

void	format_s(va_list *ap, t_info *info)
{
	char	*str;
	int		len;

	str = va_arg(*ap, char *);
	if (str == 0)
		len = 6;
	else
		len = ft_strlen(str);
	if (info->pre < len && info->pre >= 0)
		len = info->pre;
	if (str == 0)
	{
		if (len < info->wid)
			print_format_s("(null)", info, len);
		else
			ft_write(info, "(null)", len);
	}
	else
	{
		if (len < info->wid)
			print_format_s(str, info, len);
		else
			ft_write(info, str, len);
	}
}

void	print_format_c(int i, char *str, t_info *info)
{
	if (info->flag_mi == 1)
	{
		ft_memset(str, ' ', info->wid);
		str[0] = i;
	}
	else if (info->flag_mi == 0 && info->flag_ze == 0)
	{
		ft_memset(str, ' ', info->wid - 1);
		str[info->wid - 1] = i;
	}	
	else if (info->flag_mi == 0 && info->flag_ze == 1)
	{
		ft_memset(str, '0', info->wid - 1);
		str[info->wid - 1] = i;
	}
	ft_write(info, str, info->wid);
}

void	format_c(va_list *ap, t_info *info)
{
	char	*str;
	int		i;

	i = va_arg(*ap, int);
	if (info->wid > 1)
	{
		str = malloc(info->wid);
		if (str == 0)
		{
			info->ret = -1;
			return ;
		}
		print_format_c(i, str, info);
		free(str);
	}
	else
	{
		if (write(1, &i, 1) < 0)
		{
			info->ret = -1;
			return ;
		}
		info->ret += 1;
	}
}

void	format_else(t_info *info)
{
	char	c;
	char	*str;

	c = info->format;
	if (info->wid > 1)
	{
		str = malloc(info->wid);
		if (str == 0)
		{
			info->ret = -1;
			return ;
		}
		print_format_c(c, str, info);
		free(str);
	}
	else
	{
		if (write(1, &c, 1) < 0)
		{
			info->ret = -1;
			return ;
		}
		info->ret += 1;
	}
}
