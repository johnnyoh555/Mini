/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:11:15 by jooh              #+#    #+#             */
/*   Updated: 2023/12/16 16:47:30 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_write_files(t_info *info, char **outfiles)
{
	int	idx;
	int	fd;

	idx = 0;
	while (outfiles[idx])
	{
		if (idx)
			close(fd);
		if (check_file_name(info, outfiles, idx + 1))
			return (-1);
		if (ft_strncmp(outfiles[idx], ">>", 3) == 0)
			fd = open(outfiles[idx + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			fd = open(outfiles[idx + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
		{
			err_seq(outfiles[idx + 1], 0, 1, 1);
			break ;
		}
		idx += 2;
	}
	return (fd);
}

static int	open_read_files(t_info *info, char **infiles)
{
	int	idx;
	int	fd;

	idx = 0;
	while (infiles[idx])
	{
		if (idx)
			close(fd);
		if (ft_strncmp(infiles[idx], "<", 2) == 0)
		{
			if (check_file_name(info, infiles, idx + 1))
				return (-1);
		}
		fd = open(infiles[idx + 1], O_RDONLY);
		if (fd == -1)
		{
			err_seq(infiles[idx + 1], 0, 1, 1);
			break ;
		}
		idx += 2;
	}
	return (fd);
}

int	get_fds(t_command *command, t_info *info, int in, int out)
{
	if (command->infiles == 0)
		info->fd_read = in;
	else
		info->fd_read = open_read_files(info, command->infiles);
	if (info->fd_read == -1)
		return (1);
	if (command->outfiles == 0)
		info->fd_write = out;
	else
		info->fd_write = open_write_files(info, command->outfiles);
	if (info->fd_write == -1)
	{
		if (info->fd_read != 0)
			close(info->fd_read);
		return (1);
	}
	return (0);
}
