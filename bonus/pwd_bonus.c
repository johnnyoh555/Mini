/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:56:25 by jooh              #+#    #+#             */
/*   Updated: 2023/12/26 14:22:42 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	builtin_pwd(char **cmd, t_info *info)
{
	char	*pwd;

	(void)cmd;
	(void)info;
	pwd = getcwd(0, 0);
	if (pwd == 0)
	{
		printf("%s\n", info->pwd);
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
