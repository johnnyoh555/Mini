/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:07:47 by jooh              #+#    #+#             */
/*   Updated: 2023/12/12 18:35:25 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cpy_normal_str(char *str, char *ret, int len)
{
	char	*normal;
	char	*tmp;

	normal = ft_calloc(len + 1, 1);
	ft_memcpy(normal, str, len);
	if (ret == 0)
		ret = ft_strjoin("", normal);
	else
	{
		tmp = ft_strjoin(ret, normal);
		free(ret);
		ret = tmp;
	}
	return (ret);
}

char	*change_env(char *str, t_info *info)
{
	char	*env;
	char	*normal;
	char	*ret;
	int		len;

	ret = 0;
	while (*str)
	{
		len = 0;
		while (str[len] && str[len] != '$')
			len++;
		ret = cpy_normal_str(str, ret, len);
		if (*str == '$')
			str++;
		if (!(ft_isalpha(*str) || *str == '_'))
		{
			str++;
			ret = normal;
		}
		else
		{
			while (ft_isalnum(*str) || *str == '_')
		}
	}
}
