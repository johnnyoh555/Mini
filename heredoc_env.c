/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:01:28 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/24 15:19:27 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((str[len] == '$') && str[len + 1] != 0
			&& !(str[len + 1] == '"' && *d_flag == 1))
			break ;
		len++;
	}
	return (len);
}

static char	*cpy_dollar(char *ret)
{
	char	*tmp;

	tmp = ft_strjoin(ret, "$");
	free(ret);
	return (tmp);
}

char	*heredoc_change_env(char *str, t_info *info, int d_flag, int s_flag)
{
	char	*ret;
	int		len;
	char	*tmp;

	tmp = str;
	ret = ft_strdup("");
	while (*str)
	{
		len = return_str_len(str, &d_flag, &s_flag);
		ret = cpy_normal_str(str, ret, len);
		str += len;
		if (*str == '$')
		{
			len = return_env_len(str);
			if (len == 1)
				ret = cpy_dollar(ret);
			else
				ret = add_quote_join(ret, cpy_env_str(info, str, len), 1);
			str += len;
		}
	}
	free(tmp);
	return (ret);
}
