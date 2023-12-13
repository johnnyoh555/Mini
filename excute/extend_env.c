/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:22:34 by jooh              #+#    #+#             */
/*   Updated: 2023/12/12 18:03:07 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_env_outfiles(char **outfiles, t_info *info)
{
	int	idx;

	idx = 0;
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
	while (infiles[idx])
	{
		if (!ft_strncmp(infiles[idx], "<", 2)
			&& ft_strchr(infiles[idx + 1], '$'))
			infiles[idx + 1] = change_env(infiles[idx], info);
		idx += 2;
	}
}

static void	check_env_cmd(char **cmd, t_info *info)
{
	int	idx;

	idx = 0;
	while (cmd[idx])
	{
		if (ft_strchr(cmd[idx], '$'))
			cmd[idx] = change_env(cmd[idx], info);
		idx++;
	}
}

void	extend_env(t_command *command, t_info *info)
{
	while (command)
	{
		check_env_cmd(command->exprs, info);
		check_env_infiles(command->infiles, info);
		check_env_outfiles(command->outfiles, info);
		command = command->next;
	}
}
