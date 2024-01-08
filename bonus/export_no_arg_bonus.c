/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:34:24 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 14:22:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*add_quotes(char *str)
{
	char	*ret;
	int		i;

	ret = ft_calloc(ft_strlen(str) + 3, 1);
	i = 0;
	while (1)
	{
		ret[i] = str[i];
		if (ret[i] == '=')
			break ;
		i++;
	}
	ret[i + 1] = '"';
	i++;
	while (str[i])
	{
		ret[i + 1] = str[i];
		i++;
	}
	ret[i + 1] = '"';
	free(str);
	return (ret);
}

static char	**ft_duparr(char **envp)
{
	char	**ret;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ret = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		if (ft_strchr(ret[i], '='))
			ret[i] = add_quotes(ret[i]);
		i++;
	}
	return (ret);
}

void	sort_by_ascii(char **envp, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	show_evs(t_info *info)
{
	char	**cpy_envp;
	int		i;

	cpy_envp = ft_duparr(info->envp);
	i = 0;
	while (info->envp[i])
		i++;
	sort_by_ascii(cpy_envp, i);
	i = 0;
	while (cpy_envp[i])
	{
		printf("declare -x %s\n", cpy_envp[i]);
		i++;
	}
	i = 0;
	while (cpy_envp[i])
	{
		free(cpy_envp[i]);
		i++;
	}
	free(cpy_envp);
	return (0);
}

int	builtin_export(char **cmd, t_info *info)
{
	int	idx;
	int	ret;

	ret = 0;
	if (cmd[1] == 0)
	{
		show_evs(info);
		return (0);
	}
	else
	{
		idx = 1;
		while (cmd[idx])
		{
			if (make_ev(info, cmd[idx]))
				ret = 1;
			idx++;
		}
	}
	return (ret);
}
