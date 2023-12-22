/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:00:06 by jooh              #+#    #+#             */
/*   Updated: 2023/12/21 13:21:35 by sungyoon         ###   ########.fr       */
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

static void	child_process(t_command *command, t_info *info, int in, int out)
{
	if (get_fds(command, info, in, out))
		exit(1);
	dup2(info->fd_read, 0);
	dup2(info->fd_write, 1);
	close(info->fd[0]);
	close(info->fd[1]);
	close(info->prev_fd);
	if (command->exprs == 0)
		exit(0);
	exit(check_what_cmd(command->exprs, info));
}

void	child(t_command *command, t_info *info)
{
	if (pipe(info->fd) == -1)
		err_seq("pipe", 0, 1, 0);
	info->pid = fork();
	if (info->pid == 0)
	{
		signal_setting(SIG_DFL, SIG_DFL);
		if (info->idx == 1)
			child_process(command, info, 0, info->fd[1]);
		else if (info->idx == info->cmd)
			child_process(command, info, info->prev_fd, 1);
		else
			child_process(command, info, info->prev_fd, info->fd[1]);
	}
	close(info->prev_fd);
	close(info->fd[1]);
	info->prev_fd = info->fd[0];
}
