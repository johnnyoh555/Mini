/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:32:32 by jooh              #+#    #+#             */
/*   Updated: 2023/12/13 20:10:12 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	go_to_builtin(char **cmd, t_info *info)
{
	if (strncmp(cmd[0], "env", 4) == 0)
		return (builtin_env(cmd, info));
	if (strncmp(cmd[0], "unset", 6) == 0)
		return (builtin_unset(cmd, info));
	if (strncmp(cmd[0], "export", 7) == 0)
		return (builtin_export(cmd, info));
	if (strncmp(cmd[0], "echo", 5) == 0)
		return (builtin_echo(cmd, info));
	if (strncmp(cmd[0], "cd", 3) == 0)
		return (builtin_cd(cmd, info));
	if (strncmp(cmd[0], "pwd", 4) == 0)
		return (builtin_pwd(cmd, info));
	if (strncmp(cmd[0], "exit", 5) == 0)
		return (builtin_exit(cmd, info));
	return (0);
}

static int	single_builtin_cmd(t_command *command, t_info *info)
{
	int		org_read;
	int		org_write;
	int		ret;

	org_read = dup(0);
	org_write = dup(1);
	if (get_fds(command, info, 0, 1))
		return (1);
	dup2(info->fd_read, 0);
	dup2(info->fd_write, 1);
	ret = go_to_builtin(command->exprs, info);
	if (info->fd_read != 0)
		close(info->fd_read);
	if (info->fd_write != 1)
		close(info->fd_write);
	dup2(org_read, 0);
	dup2(org_write, 1);
	return (ret);
}

static int	single_simple_cmd(t_command *command, t_info *info)
{
	char	*path;

	info->pid = fork();
	if (info->pid != 0)
		return (0);
	signal_setting(SIG_DFL, SIG_DFL);
	if (get_fds(command, info, 0, 1))
		exit(1);
	dup2(info->fd_read, 0);
	dup2(info->fd_write, 1);
	path = cmd_path(info, command->exprs, 0);
	if (execve(path, command->exprs, info->envp) == -1)
		err_seq(command->exprs[0], 0, 126, 0);
	free(path);
	return (0);
}

int	single_cmd(t_command *command, t_info *info)
{
	if (strncmp(command->exprs[0], "env", 4) == 0
		|| strncmp(command->exprs[0], "unset", 6) == 0
		|| strncmp(command->exprs[0], "export", 7) == 0
		|| strncmp(command->exprs[0], "echo", 5) == 0
		|| strncmp(command->exprs[0], "cd", 3) == 0
		|| strncmp(command->exprs[0], "pwd", 4) == 0
		|| strncmp(command->exprs[0], "exit", 5) == 0)
		return (single_builtin_cmd(command, info));
	else
		single_simple_cmd(command, info);
	return (-1);
}

char	*cmd_path(t_info *info, char **cmd, int idx)
{
	char	*str;
	char	*ret;

	ret = ft_strdup(cmd[0]);
	if (ft_strchr(ret, '/') && access(ret, R_OK) == 0)
		return (ret);
	free(ret);
	if (ft_strchr(cmd[0], '/'))
		err_seq(cmd[0], 0, 127, 0);
	str = ft_strjoin("/", cmd[0]);
	if (info->path == 0)
		err_seq(cmd[0], "command not found", 127, 0);
	while (info->path[idx])
	{
		ret = ft_strjoin((info->path)[idx], str);
		if (access(ret, R_OK) == 0)
			return (ret);
		free(ret);
		idx++;
	}
	free(str);
	err_seq(cmd[0], "command not found", 127, 0);
	return (0);
}
