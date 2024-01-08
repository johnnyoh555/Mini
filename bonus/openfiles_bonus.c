/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:11:15 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 14:22:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	open_write_file(t_info *info, char **outfiles, int *idx)
{
	int	fd;

	if (info->fd_write == -100)
		close(info->fd_write);
	if (check_file_name(info, outfiles, *idx + 1))
	{
		if (info->fd_read != -1)
			close(info->fd_read);
		return (-1);
	}
	if (ft_strncmp(outfiles[*idx], ">>", 3) == 0)
		fd = open(outfiles[*idx + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(outfiles[*idx + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		err_seq(outfiles[*idx + 1], 0, 1, 1);
		if (info->fd_read != -1)
			close(info->fd_read);
		return (fd);
	}
	*idx += 2;
	return (fd);
}

static int	open_read_file(t_info *info, char **infiles, int *idx)
{
	int	fd;

	if (info->fd_read != -100)
		close(info->fd_read);
	if (ft_strncmp(infiles[*idx], "<", 2) == 0)
	{
		if (check_file_name(info, infiles, *idx + 1))
		{
			if (info->fd_write != -1)
				close(info->fd_write);
			return (-1);
		}
	}
	fd = open(infiles[*idx + 1], O_RDONLY);
	if (fd == -1)
	{
		err_seq(infiles[*idx + 1], 0, 1, 1);
		if (info->fd_write != -1)
			close(info->fd_write);
		return (fd);
	}
	*idx += 2;
	return (fd);
}

int	get_fds(t_command *command, t_info *info, int in, int out)
{
	int	idx;
	int	iidx;
	int	oidx;

	idx = 0;
	iidx = 0;
	oidx = 0;
	info->fd_read = -100;
	info->fd_write = -100;
	while (idx < command->file_cnt)
	{
		if (command->file_flag[idx] == C_INPUT || \
			command->file_flag[idx] == C_HEREDOC)
			info->fd_read = open_read_file(info, command->infiles, &iidx);
		else
			info->fd_write = open_write_file(info, command->outfiles, &oidx);
		if (info->fd_read == -1 || info->fd_write == -1)
			return (1);
		idx++;
	}
	if (info->fd_read == -100)
		info->fd_read = in;
	if (info->fd_write == -100)
		info->fd_write = out;
	return (0);
}
