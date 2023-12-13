/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:11:15 by jooh              #+#    #+#             */
/*   Updated: 2023/12/13 15:13:00 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_write_files(char **outfiles, int ret)
{
	int	idx;
	int	fd;

	if (outfiles == 0)
		return (ret);
	idx = 0;
	while (outfiles[idx])
	{
		if (idx)
			close(fd);
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

int	open_read_files(char **infiles, int ret)
{
	int	idx;
	int	fd;

	if (infiles == 0)
		return (ret);
	idx = 0;
	while (infiles[idx])
	{
		if (idx)
			close(fd);
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
