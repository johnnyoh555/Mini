/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:45:54 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 14:22:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	cnt_quote(char *str)
{
	int	len;
	int	d_flag;
	int	s_flag;
	int	cnt;

	len = 0;
	cnt = 0;
	d_flag = 0;
	s_flag = 0;
	while (str[len])
	{
		if (str[len] == '"' && s_flag == 0)
		{
			cnt++;
			d_flag = !d_flag;
		}
		if (str[len] == '\'' && d_flag == 0)
		{
			cnt++;
			s_flag = !s_flag;
		}
		len++;
	}
	return (cnt);
}

static int	get_str_len(char *str, char quote)
{
	int	len;

	len = 0;
	if (quote == 0)
	{
		while (str[len] && str[len] != '"' && str[len] != '\'')
			len++;
	}
	else
	{
		while (str[len] && str[len] != quote)
			len++;
	}
	return (len);
}

static void	copy_without_quotes(char **str, char **ret, int flag)
{
	int	len;

	if (flag == 0)
	{
		len = get_str_len(*str, 0);
		ft_memcpy(*ret, *str, len);
		*ret += len;
		*str += len;
	}
	else
	{
		(*str)++;
		len = get_str_len(*str, *(*str - 1));
		ft_memcpy(*ret, *str, len);
		*ret += len;
		*str += len;
		(*str)++;
	}
}

char	*remove_quote(char *str, int flag)
{
	int		quotes;
	char	*ret;
	char	*ret_tmp;
	char	*str_tmp;

	str_tmp = str;
	quotes = cnt_quote(str);
	ret = ft_calloc(ft_strlen(str) + 1 - quotes, 1);
	ret_tmp = ret;
	while (*str)
	{
		if (*str != '\'' && *str != '"')
			copy_without_quotes(&str, &ret, 0);
		else
			copy_without_quotes(&str, &ret, 1);
	}
	if (flag)
		free(str_tmp);
	return (ret_tmp);
}
