/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:22:42 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/20 11:13:00 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_env(t_info *info, char *key, char *value)
{
	int		size;
	int		idx;
	char	**envp;

	size = 0;
	while (info->envp[size])
		size++;
	envp = ft_calloc(sizeof(char *), (size + 2));
	idx = 0;
	while (idx < size)
	{
		envp[idx] = ft_strdup(info->envp[idx]);
		free(info->envp[idx]);
		idx++;
	}
	envp[idx] = ft_strjoin(key, value);
	free(info->envp);
	info->envp = envp;
}

static void	add_shell_level(t_info *info, int idx)
{
	char	*str;
	int		nbr;

	nbr = ft_atoi(ft_strchr(info->envp[idx], '=') + 1) + 1;
	if (nbr < 0)
		nbr = 0;
	else if (nbr > 1000)
		nbr = 1;
	if (nbr == 1000)
		str = ft_strdup("");
	else
		str = ft_itoa(nbr);
	free(info->envp[idx]);
	info->envp[idx] = ft_strjoin("SHLVL=", str);
	free(str);
}

static int	env_search(t_info *info, char *findstr)
{
	int	idx;

	idx = 0;
	while (info->envp && info->envp[idx])
	{
		if (!ft_strncmp(info->envp[idx], findstr, ft_strlen(findstr)))
			return (idx);
		idx++;
	}
	return (-1);
}

void	env_setting(t_info *info)
{
	int		ret;
	char	*str;

	ret = env_search(info, "SHLVL=");
	if (ret != -1)
		add_shell_level(info, ret);
	else
		make_env(info, "SHLVL=", "1");
	ret = env_search(info, "PWD=");
	str = getcwd(0, 0);
	if (ret == -1 && str)
		make_env(info, "PWD=", str);
	free(str);
	ret = env_search(info, "OLDPWD=");
	if (ret == -1)
		make_env(info, "OLDPWD", "");
}
