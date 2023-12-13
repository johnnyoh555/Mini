/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:00:06 by jooh              #+#    #+#             */
/*   Updated: 2023/12/13 14:06:58 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_what_cmd(char **cmd, t_info *info)
{
	char	*path;

	if (strncmp(cmd[0], "env", 4) == 0)
		return (builtin_env(cmd, info));
	else if (strncmp(cmd[0], "unset", 6) == 0)
		return (builtin_unset(cmd, info));
	else if (strncmp(cmd[0], "export", 7) == 0)
		return (builtin_export(cmd, info));
	else if (strncmp(cmd[0], "echo", 5) == 0)
		return (builtin_echo(cmd, info));
	else if (strncmp(cmd[0], "cd", 3) == 0)
		return (builtin_cd(cmd, info));
	else if (strncmp(cmd[0], "pwd", 4) == 0)
		return (builtin_pwd(cmd, info));
	else if (strncmp(cmd[0], "exit", 5) == 0)
		return (builtin_exit(cmd, info));
	else
	{
		path = cmd_path(info, cmd, 0);
		if (execve(path, cmd, info->envp) == -1)
			err_seq(cmd[0], 0, 126, 0);
		free(path);
	}
	return (0);
}

static void	first_child(t_command *command, t_info *info)
{
	int		fd_read;

	fd_read = open_read_files(command->infiles);
	dup2(fd_read, 0);
	dup2((info->fd)[1], 1);
	close_pipe(info);
	exit(check_what_cmd(command->exprs, info));
}

static void	last_child(t_command *command, t_info *info)
{
	int		fd_write;

	fd_write = open_write_files(command->outfiles);
	dup2((info->fd)[(info->cmd * 2) - 4], 0);
	dup2(fd_write, 1);
	close_pipe(info);
	exit(check_what_cmd(command->exprs, info));
}

static void	other_childs(t_command *command, t_info *info)
{
	int		*fd;

	fd = info->fd;
	dup2(fd[(info->idx) * 2 - 4], 0);
	dup2(fd[(info->idx) * 2 - 1], 1);
	close_pipe(info);
	exit(check_what_cmd(command->exprs, info));
}

void	child(t_command *command, t_info *info)
{
	info->pid = fork();
	if (info->pid == 0)
	{
		signal_setting(SIG_DFL, SIG_DFL);
		if (info->idx == 1)
			first_child(command, info);
		else if (info->idx == info->cmd)
			last_child(command, info);
		else
			other_childs(command, info);
	}
}
