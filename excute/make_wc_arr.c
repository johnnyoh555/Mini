/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_wc_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:28:59 by jooh              #+#    #+#             */
/*   Updated: 2023/12/17 14:18:59 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**make_wc_to_arr(char *name, char **wc, int flag)
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
	if (flag == 1)
		ret[idx] = ft_strjoin(name, "/");
	else
		ret[idx] = ft_strdup(name);
	free(wc);
	return (ret);
}

static int	check_files(char *name, char **arr)
{
	int		idx;
	char	*tmp;

	idx = -1;
	while (arr[++idx])
	{
		if (arr[idx][0] != '*')
		{
			tmp = remove_quote(arr[idx], 0);
			if (idx == 0 && ft_strncmp(name, tmp, ft_strlen(tmp)) != 0)
					name = 0;
			else
				name = ft_strnstr(name, tmp, ft_strlen(name));
			if (name == 0)
			{
				free(tmp);
				return (0);
			}
			name += ft_strlen(tmp);
			free(tmp);
		}
	}
	if (arr[idx - 1][0] != '*' && *name != 0)
		return (0);
	return (1);
}

int	make_wc_arr_normal(DIR *dir, char **arr, char ***wc)
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
				*wc = make_wc_to_arr(dp->d_name, *wc, 0);
			cnt++;
		}
	}
	return (cnt);
}

int	make_wc_arr_hidden(DIR *dir, char **arr, char ***wc)
{
	int				cnt;
	struct dirent	*dp;

	cnt = 0;
	while (1)
	{
		dp = readdir(dir);
		if (dp == 0)
			break ;
		if (check_files(dp->d_name, arr))
		{
			if (*wc == 0)
			{
				*wc = ft_calloc(sizeof(char *), 2);
				(*wc)[0] = ft_strdup(dp->d_name);
			}
			else
				*wc = make_wc_to_arr(dp->d_name, *wc, 0);
			cnt++;
		}
	}
	return (cnt);
}

int	make_wc_arr_directory(DIR *dir, char **arr, char ***wc)
{
	int				cnt;
	struct dirent	*dp;

	cnt = 0;
	while (1)
	{
		dp = readdir(dir);
		if (dp == 0)
			break ;
		if (check_files(dp->d_name, arr) && dp->d_type == DT_DIR
			&& dp->d_name[0] != '.')
		{
			if (*wc == 0)
			{
				*wc = ft_calloc(sizeof(char *), 2);
				(*wc)[0] = ft_strjoin(dp->d_name, "/");
			}
			else
				*wc = make_wc_to_arr(dp->d_name, *wc, 1);
			cnt++;
		}
	}
	return (cnt);
}
