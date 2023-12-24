/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:22:34 by jooh              #+#    #+#             */
/*   Updated: 2023/12/24 15:15:12 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_env_cmd(t_command *command, t_info *info)
{
	int	idx;

	idx = 0;
	if (command->exprs == 0)
		return (0);
	while (command->exprs[idx])
	{
		if (ft_strchr(command->exprs[idx], '$'))
			command->exprs[idx] = change_env(command->exprs[idx], info);
		if (ft_strlen(command->exprs[0]) == 0 && command->exprs[1] == 0)
			return (1);
		if (ft_strlen(command->exprs[idx]) == 0)
		{
			erase_vector(&command->exprs, idx, 0, 0);
			continue ;
		}
		wc_and_quotes(command, &idx);
	}
	return (0);
}

char	*add_quote_join(char *ret, char *str, int d_flag)
{
	char	*tmp;

	if (d_flag == 0 && ft_strlen(str))
	{
		tmp = ft_strjoin("\"", str);
		free(str);
		str = ft_strjoin(tmp, "\"");
		free(tmp);
	}
	tmp = ft_strjoin(ret, str);
	free(ret);
	free(str);
	return (tmp);
}

int	extend_env(t_command *command, t_info *info)
{
	while (command)
	{
		if (check_env_cmd(command, info))
		{
			info->exit_code = 0;
			return (1);
		}
		command = command->next;
	}
	return (0);
}

char	*env_to_str(t_info *info, char *str, int len)
{
	int		idx;
	char	*env;

	idx = 0;
	while (info->envp[idx])
	{
		if (ft_strncmp(str, info->envp[idx], len) == 0
			&& (info->envp[idx][len] == 0 || info->envp[idx][len] == '='))
		{
			if (info->envp[idx][len] == 0 || (info->envp[idx][len] == '='
				&& info->envp[idx][len + 1] == 0))
				return (ft_strdup(""));
			else
			{
				env = ft_strdup(info->envp[idx] + len + 1);
				return (env);
			}
		}
		idx++;
	}
	return (ft_strdup(""));
}
