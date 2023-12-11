/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:55 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/11 20:02:12 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak(void)
{
	system("leaks minishell");
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", ft_strlen(rl_line_buffer));
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_setting(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

int	main(int argc, char **argv, char **envp)
{
	atexit(leak);
	char		*str;
	t_tokenlst	*list;
	t_ptree		*tree;

	(void)argc;
	(void)argv;
	(void)envp;
	signal_setting();
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			break ;
		list = tokenizer_parse(str);
		if (list != NULL)
		{
			tree = parser_cmd(&list);
			if (parser_error(tree, list) == 0)
				parser_tree_order(tree, NULL);
			parser_tree_all_free(tree);
		}
		add_history(str);
		free(str);
	}
	return (0);
}
