/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:01:28 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/15 16:08:33 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_str_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '$')
			break ;
		len++;
	}
	return (len);
}

char	*heredoc_change_env(char *str, t_info *info)
{
	char	*ret;
	int		len;
	char	*tmp;

	tmp = str;
	ret = ft_strdup("");
	while (*str)
	{
		len = return_str_len(str);
		ret = cpy_normal_str(str, ret, len);
		str += len;
		if (*str == '$')
		{
			len = return_env_len(str);
			ret = cpy_env_str(info, str, ret, len);
			str += len;
		}
	}
	free(tmp);
	return (ret);
}
