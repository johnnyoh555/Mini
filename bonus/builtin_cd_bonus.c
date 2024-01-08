/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:34:26 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 14:22:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	change_o_pwd(t_info *info, char *o_pwd)
{
	int	idx;

	idx = 0;
	if (o_pwd == 0)
		o_pwd = ft_strdup("");
	while (info->envp[idx])
	{
		if (ft_strncmp(info->envp[idx], "OLDPWD", 6) == 0
			&& (info->envp[idx][6] == 0 || info->envp[idx][6] == '='))
		{
			free(info->envp[idx]);
			info->envp[idx] = ft_strjoin("OLDPWD=", o_pwd);
			break ;
		}
		idx++;
	}
	free(o_pwd);
	return ;
}

static char	*make_pwd(t_info *info, char *cmd)
{
	char	*ret;
	char	*tmp;

	if (info->pwd == 0)
		tmp = ft_strdup("");
	else
		tmp = ft_strjoin(info->pwd, "/");
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ret);
}

static void	change_pwd(t_info *info, char *n_pwd, char *o_pwd, char *cmd)
{
	int	idx;

	idx = 0;
	change_o_pwd(info, o_pwd);
	if (n_pwd == 0 && cmd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories:", 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		n_pwd = make_pwd(info, cmd);
	}
	while (info->envp[idx])
	{
		if (ft_strncmp(info->envp[idx], "PWD", 3) == 0
			&& (info->envp[idx][3] == 0 || info->envp[idx][3] == '='))
		{
			free(info->envp[idx]);
			info->envp[idx] = ft_strjoin("PWD=", n_pwd);
			break ;
		}
		idx++;
	}
	if (info->pwd)
		free(info->pwd);
	info->pwd = n_pwd;
}

static int	move_to_home(t_info *info)
{
	int		idx;
	char	*home;
	char	*o_pwd;

	idx = 0;
	while (info->envp[idx])
	{
		if (ft_strncmp(info->envp[idx], "HOME=", 5) == 0)
		{
			home = ft_strdup(info->envp[idx] + 5);
			o_pwd = getcwd(0, 0);
			if (chdir(home) == -1)
			{
				free(o_pwd);
				free(home);
				return (err_seq("cd", 0, 1, 1));
			}
			free(home);
			change_pwd(info, getcwd(0, 0), o_pwd, 0);
			return (0);
		}
		idx++;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (1);
}

int	builtin_cd(char **cmd, t_info *info)
{
	char	*o_pwd;

	if (cmd[1] == 0)
		return (move_to_home(info));
	else
	{
		o_pwd = getcwd(0, 0);
		if (chdir(cmd[1]) == -1)
		{
			free(o_pwd);
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		change_pwd(info, getcwd(0, 0), o_pwd, cmd[1]);
	}
	return (0);
}
