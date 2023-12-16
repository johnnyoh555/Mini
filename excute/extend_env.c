/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:22:34 by jooh              #+#    #+#             */
/*   Updated: 2023/12/16 15:15:54 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	check_env_outfiles(t_command *command, t_info *info)
// {
// 	int	idx;

// 	idx = 0;
// 	if (command->outfiles == 0)
// 		return ;
// 	while (command->outfiles[idx])
// 	{
// 		if (ft_strchr(command->outfiles[idx + 1], '$'))
// 			command->outfiles[idx + 1]
// 				= change_env(command->outfiles[idx + 1], info);
// 		idx += 2;
// 	}
// }

// static void	check_env_infiles(t_command *command, t_info *info)
// {
// 	int	idx;

// 	idx = 0;
// 	if (command->infiles == 0)
// 		return ;
// 	while (command->infiles[idx])
// 	{
// 		if (!ft_strncmp(command->infiles[idx], "<", 2)
// 			&& ft_strchr(command->infiles[idx + 1], '$'))
// 			command->infiles[idx + 1]
// 				= change_env(command->infiles[idx + 1], info);
// 		idx += 2;
// 	}
// }

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

char	*env_to_str(t_info *info, char *str, char *ret, int len)
{
	int		idx;
	char	*tmp;
	char	*env;

	idx = 0;
	while (info->envp[idx])
	{
		if (ft_strncmp(str, info->envp[idx], len) == 0
			&& (info->envp[idx][len] == 0 || info->envp[idx][len] == '='))
		{
			if (info->envp[idx][len] == 0 || (info->envp[idx][len] == '='
				&& info->envp[idx][len + 1] == 0))
				return (ret);
			else
			{
				env = ft_strdup(info->envp[idx] + len + 1);
				tmp = ft_strjoin(ret, env);
				free(ret);
				free(env);
				return (tmp);
			}
		}
		idx++;
	}
	return (ret);
}
