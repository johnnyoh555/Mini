/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wc_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:21:50 by jooh              #+#    #+#             */
/*   Updated: 2023/12/16 16:44:31 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_files(char *name, char **arr)
{
	int		idx;
	char	*tmp;

	idx = 0;
	while (arr[idx])
	{
		if (arr[idx][0] != '*')
		{
			tmp = remove_quote(arr[idx], 0);
			name = ft_strnstr(name, tmp, ft_strlen(name));
			if (name == 0)
			{
				free(tmp);
				return (0);
			}
			name += ft_strlen(tmp);
			free(tmp);
		}
		idx++;
	}
	if (arr[idx - 1][0] != '*' && *name != 0)
		return (0);
	return (1);
}

static char	**make_wc_to_arr(char *name, char **wc)
{
	char	**ret;
	int		idx;

	idx = 0;
	while (wc[idx])
			idx++;
	ret = ft_calloc(sizeof(char *), idx + 2);
	idx = 0;
	while (wc[idx])
	{
		ret[idx] = wc[idx];
		idx++;
	}
	ret[idx] = ft_strdup(name);
	free(wc);
	return (ret);
}

int	make_wc_arr(DIR *dir, char **arr, char ***wc)
{
	int				cnt;
	struct dirent	*dp;

	cnt = 0;
	while (1)
	{
		dp = readdir(dir);
		if (dp == 0)
			break ;
		if (check_files(dp->d_name, arr) && dp->d_name[0] != '.')
		{
			if (*wc == 0)
			{
				*wc = ft_calloc(sizeof(char *), 2);
				(*wc)[0] = ft_strdup(dp->d_name);
			}
			else
				*wc = make_wc_to_arr(dp->d_name, *wc);
			cnt++;
		}
	}
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
