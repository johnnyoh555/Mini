/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_search_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:15:39 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/18 17:27:32 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	heredoc_process(t_ptree *tree, t_info *info, int flag)
{
	t_command	*cmd;
	char		*tmp;
	int			ret;

	ret = 0;
	cmd = NULL;
	command_list_add_node(&cmd, command_list_create_node());
	command_list_add_redirection(&cmd, tree->expr);
	command_list_add_expr(&cmd, tree->left->expr);
	if (flag == 0)
	{
		ret = create_heredoc(cmd, info);
		tmp = ft_strdup(cmd->infiles[1]);
		free(tree->left->expr);
		tree->left->expr = tmp;
	}
	else
		delete_heredoc_files(cmd);
	command_list_all_free(cmd);
	return (ret);
}

int	heredoc_search(t_ptree *tree, t_info *info, int flag)
{
	t_command	*cmd;

	cmd = NULL;
	if (tree == NULL)
		return (0);
	if (heredoc_search(tree->left, info, flag))
		return (1);
	if (tree->type == P_REDIRECTION && !ft_strncmp(tree->expr, "<<", 3))
	{
		if (heredoc_process(tree, info, flag))
			return (1);
	}
	if (heredoc_search(tree->right, info, flag))
		return (1);
	return (0);
}
