/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:19:59 by jooh              #+#    #+#             */
/*   Updated: 2023/12/18 17:28:39 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	err_seq(char *str, char *err, int ex, int flag)
{
	if (err == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\n", 2);
	}
	if (flag)
		return (ex);
	exit(ex);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (1)
	{
		if (*str1 == 0 && *str2 == 0)
			return (0);
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

void	erase_vector(char ***arr, int i, int size, int flag)
{
	int		idx;
	char	**new_ev;

	idx = -1;
	while ((*arr)[size])
		size++;
	new_ev = ft_calloc(sizeof(char *), (size));
	while (++idx + flag <= size - 1)
	{
		if (idx == i)
		{
			free((*arr)[idx]);
			flag = 1;
			if (idx + flag == size)
				break ;
		}
		new_ev[idx] = ft_strdup((*arr)[idx + flag]);
		free((*arr)[idx + flag]);
	}
	free(*arr);
	*arr = new_ev;
}
