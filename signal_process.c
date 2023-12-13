/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:29:49 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/13 13:23:53 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

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

void	signal_child_handler(int signo)
{
	if (signo == SIGINT)
		printf("\n");
	else if (signo == SIGQUIT)
		printf("Quit : 3\n");
}

void	signal_heredoc_handler(int signo)
{
	if (signo == SIGINT)
		g_exit_status = 1;
}

void	signal_setting(void (quit)(int), void (interrupt)(int))
{
	rl_catch_signals = 0;
	signal(SIGQUIT, quit);
	signal(SIGINT, interrupt);
}
