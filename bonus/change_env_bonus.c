/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:07:47 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 14:22:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*cpy_env_str(t_info *info, char *str, int len)
{
	char	*exit_code;
	char	*arr;

	if (!(ft_isalpha(*(str + 1)) || *(str + 1) == '_'))
	{
		if (*(str + 1) == '?')
		{
			exit_code = ft_itoa(info->exit_code);
			return (exit_code);
		}
		else
		{
			arr = ft_calloc(len + 1, 1);
			ft_memcpy(arr, str, len);
			return (arr);
		}
	}
	return (env_to_str(info, str + 1, len - 1));
}

char	*cpy_normal_str(char *str, char *ret, int len)
{
	char	*normal;
	char	*tmp;

	normal = ft_calloc(len + 1, 1);
	ft_memcpy(normal, str, len);
	tmp = ft_strjoin(ret, normal);
	free(ret);
	ret = tmp;
	free(normal);
	return (ret);
}

static int	return_str_len(char *str, int *d_flag, int *s_flag)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '"' && *s_flag == 0)
			*d_flag = !*d_flag;
		if (str[len] == '\'' && *d_flag == 0)
			*s_flag = !*s_flag;
		if ((str[len] == '$' && *s_flag == 0) && str[len + 1] != 0
			&& !(str[len + 1] == '"' && *d_flag == 1))
			break ;
		len++;
	}
	return (len);
}

int	return_env_len(char *str)
{
	int	len;

	len = 1;
	if (str[len] == ' ' || str[len] == '\'' || str[len] == '"')
		return (1);
	if (!(ft_isalpha(str[len]) || str[len] == '_'))
		return (2);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

char	*change_env(char *str, t_info *info)
{
	char	*ret;
	int		len;
	int		d_flag;
	int		s_flag;
	char	*tmp;

	tmp = str;
	d_flag = 0;
	s_flag = 0;
	ret = ft_strdup("");
	while (*str)
	{
		len = return_str_len(str, &d_flag, &s_flag);
		ret = cpy_normal_str(str, ret, len);
		str += len;
		if (*str == '$' && s_flag == 0)
		{
			len = return_env_len(str);
			if (*(str + 1) != '"' && *(str + 1) != '\'')
				ret = add_quote_join(ret, cpy_env_str(info, str, len), d_flag);
			str += len;
		}
	}
	free(tmp);
	return (ret);
}
