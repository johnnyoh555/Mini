/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wc_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:21:50 by jooh              #+#    #+#             */
/*   Updated: 2023/12/17 16:04:01 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_dir(char **arr)
{
	int	idx;
	int	idx2;

	idx = 0;
	idx2 = 0;
	while (arr[idx])
		idx++;
	idx--;
	if (idx == 0)
		return (0);
	while (arr[idx][idx2])
	{
		if (arr[idx][idx2] != '/')
			return (0);
		idx2++;
	}
	free(arr[idx]);
	arr[idx] = 0;
	return (1);
}

int	make_wc_arr(DIR *dir, char **arr, char ***wc)
{
	int				cnt;

	if (check_dir(arr))
		cnt = make_wc_arr_directory(dir, arr, wc);
	else if (arr[0][0] == '.')
		cnt = make_wc_arr_hidden(dir, arr, wc);
	else
		cnt = make_wc_arr_normal(dir, arr, wc);
	return (cnt);
}

static void	add_wc_to_cmd(t_command *command, char **wc, int idx, int size)
{
	int		wc_size;
	int		cmd_size;
	char	**tmp;

	tmp = ft_calloc(sizeof(char *), size);
	cmd_size = -1;
	wc_size = 0;
	while (command->exprs[++cmd_size])
	{
		if (cmd_size == idx)
		{
			free(command->exprs[cmd_size]);
			while (wc[wc_size])
			{
				tmp[cmd_size + wc_size] = wc[wc_size];
				wc_size++;
			}
			wc_size--;
			continue ;
		}
		tmp[cmd_size + wc_size] = command->exprs[cmd_size];
	}
	free(command->exprs);
	free(wc);
	command->exprs = tmp;
}

int	check_with_arr(t_command *command, char **arr, int *idx)
{
	DIR		*dir;
	int		cnt;
	char	**wc;
	int		wc_size;
	int		cmd_size;	

	wc = 0;
	wc_size = 0;
	cmd_size = 0;
	dir = opendir(".");
	if (dir == 0)
		return (0);
	cnt = make_wc_arr(dir, arr, &wc);
	if (cnt)
	{
		while (wc[wc_size])
			wc_size++;
		while (command->exprs[cmd_size])
			cmd_size++;
		sort_by_ascii(wc, cnt);
		add_wc_to_cmd(command, wc, *idx, wc_size + cmd_size);
		(*idx) += cnt;
	}
	closedir(dir);
	return (cnt);
}

int	check_last_wc(char *name, char *arr)
{
	while (1)
	{
		name = ft_strnstr(name, arr, ft_strlen(name));
		if (name == 0)
			return (0);
		name += ft_strlen(arr);
		if (*name == 0)
			return (1);
	}
	return (0);
}
