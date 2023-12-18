/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:14:09 by jooh              #+#    #+#             */
/*   Updated: 2023/12/18 17:28:36 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	delete_env(t_info *info, char *arg, int flag, int size)
{
	int		idx;
	char	**new_ev;
	int		len;

	len = ft_strlen(arg);
	idx = -1;
	while (info->envp[size])
		size++;
	new_ev = ft_calloc(sizeof(char *), (size));
	while (++idx + flag <= size - 1 && info->envp[idx])
	{
		if (!ft_strncmp(arg, info->envp[idx], len)
			&& (info->envp[idx][len] == '=' || info->envp[idx][len] == 0))
		{
			free(info->envp[idx]);
			flag = 1;
			if (idx + flag == size)
				break ;
		}
		new_ev[idx] = ft_strdup(info->envp[idx + flag]);
		free(info->envp[idx + flag]);
	}
	free(info->envp);
	info->envp = new_ev;
}

static int	check_same_ev(char **envp, char *arg)
{
	int	len;
	int	idx;

	len = ft_strlen(arg);
	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], arg, len) == 0
			&& (envp[idx][len] == '=' || envp[idx][len] == 0))
			return (1);
		idx++;
	}
	return (0);
}

static int	check_valid(char *arg)
{
	int	i;

	if (!(ft_isalpha(*arg) || *arg == '_'))
		return (1);
	i = 1;
	while (arg[i])
	{
		if (!(arg[i] == '_' || ft_isalnum(arg[i])))
			return (1);
		i++;
	}
	return (0);
}

static int	remove_ev(t_info *info, char *arg)
{
	if (*arg == '-' && *(arg + 1) == 0)
		return (0);
	if (check_valid(arg))
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	if (check_same_ev(info->envp, arg))
		delete_env(info, arg, 0, 0);
	return (0);
}

int	builtin_unset(char **cmd, t_info *info)
{
	int	idx;
	int	ret;

	ret = 0;
	if (cmd[1] == 0)
		return (0);
	idx = 1;
	while (cmd[idx])
	{
		if (remove_ev(info, cmd[idx]))
			ret = 1;
		idx++;
	}
	return (ret);
}
