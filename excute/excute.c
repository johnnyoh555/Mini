/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:00:49 by jooh              #+#    #+#             */
/*   Updated: 2023/12/12 15:56:46 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->cmd * 2 - 2)
	{
		if (close((info->fd)[i]) == -1)
			err_seq("close", 0, 1, 0);
		i++;
	}
}

static void	im_mario(t_info *info)
{
	int	*fd;
	int	i;

	if (info->cmd == 1)
		return ;
	fd = ft_calloc(sizeof(int), ((info->cmd * 2) - 2));
	info->fd = fd;
	i = 0;
	while (i < ((info->cmd * 2) - 2))
	{
		if (pipe(fd + i) == -1)
			err_seq("pipe", 0, 1, 0);
		i += 2;
	}
}

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
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
		i++;
	}
	return (ret);
}

// static void	end_seq(t_info *info)
// {
// 	int	i;

// 	i = -1;
// 	if (info->path)
// 	{
// 		while ((info->path)[++i])
// 			free((info->path)[i]);
// 		free(info->path);
// 	}
// 	free(info->fd);
// }

int	execute(t_command *command, t_info *info)
{
	int	ret;

	info->idx = 1;
	if (info->cmd == 1)
	{
		ret = single_cmd(command, info);
		if (ret == -1)
			return (wait_dl(info));
		return (ret);
	}
	im_mario(info);
	while (info->idx <= info->cmd)
	{
		child(command, info);
		command = command->next;
		info->idx++;
	}
	close_pipe(info);
	ret = wait_dl(info);
	return (ret);
}
