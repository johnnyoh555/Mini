/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:31:41 by jooh              #+#    #+#             */
/*   Updated: 2023/12/12 15:57:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_nflag(char *arg)
{
	if (*arg != '-')
		return (0);
	arg++;
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
			printf(" ");
		printf("%s", arg[idx]);
		idx++;
	}
	if (flag == 0)
		printf("\n");
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
		printf("\n");
		return (0);
	}
	if (check_nflag(cmd[1]))
	{
		idx = 2;
		flag = 1;
	}
	put_echo_arg(cmd, idx, flag);
	return (0);
}
