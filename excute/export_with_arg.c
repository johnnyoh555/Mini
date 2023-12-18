/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:43:17 by jooh              #+#    #+#             */
/*   Updated: 2023/12/18 16:24:55 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_new_env(t_info *info, char *arg)
{
	int		size;
	int		idx;
	char	**new_ev;

	size = 0;
	idx = 0;
	while (info->envp[size])
		size++;
	new_ev = ft_calloc(sizeof(char *), (size + 2));
	while (idx < size && info->envp[idx])
	{
		new_ev[idx] = ft_strdup(info->envp[idx]);
		free(info->envp[idx]);
		idx++;
	}
	new_ev[idx] = ft_strdup(arg);
	free(info->envp);
	info->envp = new_ev;
}

static int	check_same_ev(char **envp, char *arg)
{
	int	len;
	int	idx;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], arg, len) == 0
			&& (envp[idx][len] == '=' || envp[idx][len] == 0))
		{
			if (arg[len] == '=')
			{
				free(envp[idx]);
				envp[idx] = ft_strdup(arg);
			}
			return (1);
		}
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
	while (arg[i] && arg[i] != '=')
	{
		if (!(arg[i] == '_' || ft_isalnum(arg[i])))
			return (1);
		i++;
	}
	return (0);
}

int	make_ev(t_info *info, char *arg)
{
	if (*arg == '-' && *(arg + 1) == 0)
		return (0);
	if (check_valid(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (check_same_ev(info->envp, arg) == 0)
		add_new_env(info, arg);
	return (0);
}
