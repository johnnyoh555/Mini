/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:22:34 by jooh              #+#    #+#             */
/*   Updated: 2023/12/13 22:20:46 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_env_outfiles(char **outfiles, t_info *info)
{
	int	idx;

	idx = 0;
	if (outfiles == 0)
		return ;
	while (outfiles[idx])
	{
		if (ft_strchr(outfiles[idx + 1], '$'))
			outfiles[idx + 1] = change_env(outfiles[idx], info);
		idx += 2;
	}
}

static void	check_env_infiles(char **infiles, t_info *info)
{
	int	idx;

	idx = 0;
	if (infiles == 0)
		return ;
	while (infiles[idx])
	{
		if (!ft_strncmp(infiles[idx], "<", 2)
			&& ft_strchr(infiles[idx + 1], '$'))
			infiles[idx + 1] = change_env(infiles[idx], info);
		idx += 2;
	}
}

static int	check_env_cmd(char **cmd, t_info *info)
{
	int	idx;

	idx = 0;
	while (cmd[idx])
	{
		if (ft_strchr(cmd[idx], '$'))
			cmd[idx] = change_env(cmd[idx], info);
		if (ft_strlen(cmd[0]) == 0)
			return (1);
		cmd[idx] = remove_quote(cmd[idx]);
		idx++;
	}
	return (0);
}

int	extend_env(t_command *command, t_info *info)
{
	while (command)
	{
		if (check_env_cmd(command->exprs, info))
		{
			info->exit_code = 0;
			return (1);
		}
		check_env_infiles(command->infiles, info);
		check_env_outfiles(command->outfiles, info);
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
