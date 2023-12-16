/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:04:21 by jooh              #+#    #+#             */
/*   Updated: 2023/12/16 14:29:46 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wc_words(char *str, int d_flag, int s_flag)
{
	int	size;

	size = 0;
	if (*str != '*')
		size++;
	while (*str)
	{
		if (*str == '"' && s_flag == 0)
			d_flag = !d_flag;
		if (*str == '\'' && d_flag == 0)
			s_flag = !s_flag;
		if (*str == '*' && s_flag == 0 && d_flag == 0)
		{
			size++;
			while (*str == '*')
				str++;
			if (*str)
				size++;
		}
		else
			str++;
	}
	return (size);
}

static int	return_wc_len(char *cmd)
{
	int	len;
	int	s_flag;
	int	d_flag;

	s_flag = 0;
	d_flag = 0;
	len = 0;
	if (cmd[len] == '*')
	{
		while (cmd[len] == '*')
			len++;
		return (len);
	}
	while (cmd[len])
	{
		if (cmd[len] == '"' && s_flag == 0)
			d_flag = !d_flag;
		if (cmd[len] == '\'' && d_flag == 0)
			s_flag = !s_flag;
		if (cmd[len] == '*' && s_flag == 0 && d_flag == 0)
			break ;
		len++;
	}
	return (len);
}

static char	**wc_checker(char *cmd, int idx)
{
	int		size;
	char	**arr;
	int		len;
	char	*ret;

	len = 0;
	size = wc_words(cmd, 0, 0);
	arr = ft_calloc(sizeof(char *), size + 1);
	while (idx < size)
	{
		len = return_wc_len(cmd);
		ret = ft_calloc(len + 1, 1);
		arr[idx] = ft_memcpy(ret, cmd, len);
		cmd += len;
		idx++;
	}
	return (arr);
}

void	wc_and_quotes(t_command *cmd, int *idx)
{
	char	**arr;
	int		i;

	arr = wc_checker(cmd->exprs[*idx], 0);
	if ((arr[0][0] != '*' && arr[1] == 0) || !check_with_arr(cmd, arr, idx))
	{
		cmd->exprs[*idx] = remove_quote(cmd->exprs[*idx], 1);
		(*idx)++;
	}
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
