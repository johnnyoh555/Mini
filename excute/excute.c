/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:00:49 by jooh              #+#    #+#             */
/*   Updated: 2023/12/22 11:31:18 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wait_dl(t_info *info)
{
	int		i;
	int		status;
	int		ret;

	i = 0;
	ret = 0;
	while (i < info->cmd)
	{
		if (wait(&status) == info->pid)
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				ret = WTERMSIG(status) + 128;
				if (ret == SIGINT + 128)
					printf("\n");
				else if (ret == SIGQUIT + 128)
					printf("Quit : 3\n");
			}
		}
		i++;
	}
	return (ret);
}

void	end_seq(t_info *info)
{
	int	i;

	i = -1;
	if (info->path)
	{
		while (info->path[++i])
			free(info->path[i]);
		free(info->path);
	}
	info->path = 0;
}

int	execute(t_command *command, t_info *info)
{
	info->idx = 1;
	if (info->cmd == 1)
	{
		info->exit_code = single_cmd(command, info);
		if (info->exit_code != -1)
			return (info->exit_code);
		signal_setting(SIG_IGN, SIG_IGN);
		info->exit_code = wait_dl(info);
		signal_setting(SIG_IGN, signal_readline_handler);
		return (info->exit_code);
	}
	info->prev_fd = dup(0);
	while (info->idx <= info->cmd)
	{
		child(command, info);
		command = command->next;
		info->idx++;
	}
	close(info->prev_fd);
	signal_setting(SIG_IGN, SIG_IGN);
	info->exit_code = wait_dl(info);
	signal_setting(SIG_IGN, signal_readline_handler);
	return (info->exit_code);
}
