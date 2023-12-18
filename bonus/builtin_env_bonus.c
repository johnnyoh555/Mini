/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:21:21 by jooh              #+#    #+#             */
/*   Updated: 2023/12/18 17:26:44 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	builtin_env(char **cmd, t_info *info)
{
	int	i;

	i = 0;
	if (cmd[1] == 0)
	{
		while (info->envp[i])
		{
			if (ft_strchr(info->envp[i], '='))
				if (printf("%s\n", info->envp[i]) == -1)
					return (1);
		i++;
		}
	}
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
