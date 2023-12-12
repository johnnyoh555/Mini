/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:55 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/12 15:25:55 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_if_path(char **strs)
{
	int	idx;

	idx = 0;
	while (strs[idx])
	{
		if (!ft_strncmp("PATH=", strs[idx], 5))
			return (0);
		idx++;
	}
	return (1);
}

static void	make_envp(t_info *info, char **strs)
{
	char	**envp;
	int		len;
	int		idx;
	int		flag;

	len = 0;
	while (strs[len] != NULL)
		len++;
	flag = check_if_path(strs);
	envp = ft_calloc(len + flag + 1, sizeof(char **));
	idx = 0;
	while (strs[idx] != NULL)
	{
		envp[idx] = ft_strdup(strs[idx]);
		idx++;
	}
	if (flag)
		envp[idx] = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	info->envp = envp;
}

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
	t_info		info;

	(void)argc;
	(void)argv;
	make_envp(&info, envp);
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
				parser_tree_order(tree, NULL, &info);
			parser_tree_all_free(tree);
		}
		add_history(str);
		free(str);
	}
	return (0);
}
