/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:29:49 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/16 15:37:16 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_readline_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", ft_strlen(rl_line_buffer));
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", ft_strlen(rl_line_buffer));
		printf("\n");
		rl_on_new_line();
		exit(128 + signo);
	}
}

void	signal_setting(void (quit)(int), void (interrupt)(int))
{
	rl_catch_signals = 0;
	signal(SIGQUIT, quit);
	signal(SIGINT, interrupt);
}
