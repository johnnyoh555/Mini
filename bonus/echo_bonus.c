/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:31:41 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 14:22:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_nflag(char *arg)
{
	if (*arg != '-')
		return (0);
	arg++;
	if (*arg != 'n')
		return (0);
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}

static void	put_echo_arg(char **arg, int start, int flag)
{
	int	idx;

	idx = start;
	while (arg[idx])
	{
		if (idx != start)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(arg[idx], 1);
		idx++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
}

int	builtin_echo(char **cmd, t_info *info)
{
	int	idx;
	int	flag;

	(void)info;
	flag = 0;
	idx = 1;
	if (cmd[1] == 0)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (cmd[idx] && check_nflag(cmd[idx]))
	{
		idx++;
		flag = 1;
	}
	put_echo_arg(cmd, idx, flag);
	return (0);
}
