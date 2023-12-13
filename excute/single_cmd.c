/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:32:32 by jooh              #+#    #+#             */
/*   Updated: 2023/12/13 14:08:06 by sungyoon         ###   ########.fr       */
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
	int		fd_read;
	int		fd_write;

	fd_read = open_read_files(command->infiles);
	fd_write = open_write_files(command->outfiles);
	if (fd_read == -1 || fd_write == -1)
		return (1);
	dup2(fd_read, 0);
	dup2(fd_write, 1);
	return (go_to_builtin(command->exprs, info));
}

static int	single_simple_cmd(t_command *command, t_info *info)
{
	int		fd_read;
	int		fd_write;
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		return (0);
	signal_setting(SIG_DFL, SIG_DFL);
	fd_read = open_read_files(command->infiles);
	fd_write = open_write_files(command->outfiles);
	if (fd_read == -1 || fd_write == -1)
		return (1);
	dup2(fd_read, 0);
	dup2(fd_write, 1);
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
		return (NULL);
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
