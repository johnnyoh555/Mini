/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_wc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:03:37 by jooh              #+#    #+#             */
/*   Updated: 2023/12/19 16:02:52 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_name_with_arr(char **file, int f_nbr, char **arr)
{
	DIR		*dir;
	int		cnt;
	char	**wc;

	wc = 0;
	dir = opendir(".");
	if (dir == 0)
		return (0);
	cnt = make_wc_arr(dir, arr, &wc);
	if (cnt == 1)
	{
		free(file[f_nbr]);
		file[f_nbr] = wc[0];
		free(wc);
		return (0);
	}
	else if (cnt != 0)
		return (1);
	closedir(dir);
	return (-1);
}

int	check_file_name(t_info *info, char **file, int f_nbr)
{
	char	*tmp;

	tmp = ft_strdup(file[f_nbr]);
	if (ft_strchr(file[f_nbr], '$'))
		file[f_nbr] = change_env(file[f_nbr], info);
	if (ft_strlen(file[f_nbr]) == 0)
	{
		err_seq(tmp, "ambiguous redirect", 1, 1);
		free(tmp);
		return (1);
	}
	free(tmp);
	if (wc_and_quotes_for_files(file, f_nbr))
		return (1);
	return (0);
}
