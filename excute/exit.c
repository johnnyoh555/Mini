/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:15:57 by jooh              #+#    #+#             */
/*   Updated: 2023/12/12 16:17:36 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wrong_exit_arg(t_info *info, char *str)
{
	if (info->cmd == 1)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static int	check_size(char *str, int minus, int idx)
{
	while (*str == '0')
		str++;
	while (str[idx])
	{
		if (!(str[idx] >= '0' && str[idx] <= '9'))
			return (1);
		idx++;
	}
	if (minus)
	{
		if (ft_strlen(str) > 19)
			return (1);
		if (ft_strlen(str) == 19
			&& ft_strncmp(str, "9223372036854775808", 19) > 0)
			return (1);
	}
	else
	{
		if (ft_strlen(str) > 19)
			return (1);
		if (ft_strlen(str) == 19
			&& ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (1);
	}
	return (0);
}

static long long	ft_atoll(t_info *info, char *str)
{
	int			minus;
	long long	value;

	value = 0;
	minus = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	if (*str == 0 || check_size(str, minus, 0))
		wrong_exit_arg(info, str);
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		if (value > 0 && minus == -1)
			value *= -1;
		value += *str - '0';
		str++;
	}
	return (value);
}

static void	right_exit(t_info *info, long long arg)
{
	long long	exit_num;

	exit_num = arg % 256;
	if (exit_num < 0)
		exit_num += 256;
	if (info->cmd == 1)
		ft_putstr_fd("exit\n", 2);
	exit(exit_num);
}

int	builtin_exit(char **cmd, t_info *info)
{
	int	idx;

	idx = 1;
	if (cmd[1] == 0)
	{
		if (info->cmd == 1)
			ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	while (cmd[idx])
	{
		ft_atoll(info, cmd[idx]);
		idx++;
	}
	if (idx != 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if (info->cmd == 1)
			ft_putstr_fd("exit\n", 2);
		exit(1);
	}
	right_exit(info, ft_atoll(info, cmd[idx]));
	return (0);
}
