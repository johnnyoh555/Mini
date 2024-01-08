/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:30:03 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/26 14:22:28 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	delete_heredoc_files(t_command *cmd)
{
	int		idx;
	int		size;

	while (cmd)
	{
		size = 0;
		while (cmd->infiles && cmd->infiles[size])
			size++;
		idx = 0;
		while (idx < size)
		{
			if (!ft_strncmp(cmd->infiles[idx], "<<", 3))
			{
				if (access(cmd->infiles[idx + 1], F_OK) == 0)
					unlink(cmd->infiles[idx + 1]);
			}
			idx += 2;
		}
		cmd = cmd->next;
	}
}

static int	wait_process(pid_t pid)
{
	int	ret;
	int	status;

	ret = 0;
	signal_setting(SIG_IGN, SIG_IGN);
	if (wait(&status) == pid)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				ret = 1;
		}
		else if (WIFSIGNALED(status))
			ret = 1;
	}
	signal_setting(SIG_IGN, signal_readline_handler);
	return (ret);
}

static void	read_heredoc(t_command *cmd, t_info *info, char *lim, int idx)
{
	char	*line;
	int		fd;

	fd = open(cmd->infiles[idx + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(lim, line, get_str_max_length(lim, line)))
			break ;
		if (cmd->inflag[idx / 2] == 1)
			line = heredoc_change_env(line, info, 0, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(lim);
	close(fd);
	exit(0);
}

int	fork_heredoc(t_command *cmd, t_info *info, char *lim, int idx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal_setting(SIG_IGN, signal_heredoc_handler);
		rl_catch_signals = 1;
		read_heredoc(cmd, info, lim, idx);
	}
	if (wait_process(pid) == 1)
	{
		delete_heredoc_files(cmd);
		info->exit_code = 1;
		return (1);
	}
	return (0);
}

int	create_heredoc(t_command *cmd, t_info *info)
{
	char	*limiter;
	int		idx;
	int		ret;

	ret = 0;
	while (cmd)
	{
		idx = 0;
		while (cmd->infiles && cmd->infiles[idx])
		{
			if (ft_strncmp(cmd->infiles[idx], "<<", 3) == 0)
			{
				limiter = make_limiter(cmd, idx);
				free(cmd->infiles[idx + 1]);
				cmd->infiles[idx + 1] = make_heredoc_file_name();
				ret = fork_heredoc(cmd, info, limiter, idx);
				free(limiter);
				if (ret == 1)
					return (1);
			}
			idx += 2;
		}
		cmd = cmd->next;
	}
	return (ret);
}
