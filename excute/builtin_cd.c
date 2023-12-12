/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:34:26 by jooh              #+#    #+#             */
/*   Updated: 2023/12/12 15:29:21 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	make_o_pwd(t_info *info, char *o_pwd)
{
	int		size;
	int		idx;
	char	**new_ev;

	size = 0;
	idx = 0;
	while (info->envp[size])
		size++;
	new_ev = ft_calloc(sizeof(char *), (size + 2));
	while (idx < size - 1)
	{
		new_ev[idx] = ft_strdup(info->envp[idx]);
		free(info->envp[idx]);
		idx++;
	}
	new_ev[idx] = ft_strjoin("OLDPWD=", o_pwd);
	new_ev[idx + 1] = ft_strdup(info->envp[idx]);
	free(info->envp[idx]);
	free(info->envp);
	info->envp = new_ev;
}

static void change_o_pwd(t_info *info, char *o_pwd)
{
	int	idx;

	idx = 0;
	while (info->envp[idx])
	{
		if (ft_strncmp(info->envp[idx], "OLDPWD", 6) == 0
			&& (info->envp[idx][6] == 0 || info->envp[idx][6] == '='))
		{
			free(info->envp[idx]);
			info->envp[idx] = ft_strjoin("OLDPWD=", o_pwd);
			free(o_pwd);
			return ;
		}
		idx++;
	}
	make_o_pwd(info, o_pwd);
	free(o_pwd);
	return ;
}

static void	change_pwd(t_info *info, char *n_pwd, char *o_pwd)
{
	int	idx;

	idx = 0;
	change_o_pwd(info, o_pwd);
	while (info->envp[idx])
	{
		if (ft_strncmp(info->envp[idx], "PWD", 3) == 0
			&& (info->envp[idx][3] == 0 || info->envp[idx][3] == '='))
		{
			free(info->envp[idx]);
			info->envp[idx] = ft_strjoin("PWD=", n_pwd);
			free(n_pwd);
			return ;
		}
		idx++;
	}
	free(n_pwd);
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
			change_pwd(info, getcwd(0, 0), o_pwd);
			return (0);
		}
		idx++;
	}
	printf("minishell: cd: HOME not set\n");
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
			return (err_seq("cd", 0, 1, 1));
		}
		change_pwd(info, getcwd(0, 0), o_pwd);
	}
	return (0);
}
