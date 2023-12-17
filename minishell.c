/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:55 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/17 16:09:13 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_path(char **strs)
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
	info->fd = 0;
	info->path = 0;
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
		envp[idx]
			= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	info->envp = envp;
	info->pwd = 0;
}

static int	parse_str(char *str, t_info *info)
{
	t_tokenlst	*list;
	t_ptree		*tree;

	if (*str == '\0')
		return (1);
	list = tokenizer_parse(str);
	if (list != NULL)
	{
		tree = parser_cmd(&list);
		if (parser_error(tree, list) == 0)
		{
			if (heredoc_search(tree, info, 0) == 0)
				parser_tree_order(tree, NULL, info);
			heredoc_search(tree, info, 1);
		}
		else
			info->exit_code = SYNTAX_ERROR_CODE;
		parser_tree_all_free(tree);
	}
	else
		info->exit_code = SYNTAX_ERROR_CODE;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_info		info;

	(void)argc;
	(void)argv;
	make_envp(&info, envp);
	env_setting(&info);
	signal_setting(SIG_IGN, signal_readline_handler);
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			break ;
		if (parse_str(str, &info) == 0)
			add_history(str);
		free(str);
	}
	printf("\033[A\033[11Cexit\n");
	exit(info.exit_code);
}
