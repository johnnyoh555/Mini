/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:28:58 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/11 20:02:18 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_cmd(t_command *cmd)
{
	print_command_list(cmd);
	return (0);
}

void	parser_tree_left_search(t_ptree *tree, t_command **cmd)
{
	if (tree->type == P_SUBCMD)
		command_list_add_node(cmd, command_list_create_node());
	else if (tree->type == P_REDIRECTION)
		command_list_add_redirection(cmd, tree->expr);
	else if (tree->type == P_EXPR)
		command_list_add_expr(cmd, tree->expr);
	parser_tree_order(tree->left, cmd);
}

void	parser_tree_order(t_ptree *tree, t_command **pcmd)
{
	t_command	*cmd;
	int			ret;

	cmd = NULL;
	if (tree == NULL)
		return ;
	if (tree->type == P_CMD)
		parser_tree_left_search(tree, &cmd);
	else
		parser_tree_left_search(tree, pcmd);
	if (tree->type == P_CMD)
	{
		if (cmd != NULL)
		{
			ret = excute_cmd(cmd);
			command_list_all_free(cmd);
			if (tree->expr != NULL && \
				((ret == 0 && ft_strncmp("||", tree->expr, 3) == 0) || \
				(ret == 1 && ft_strncmp("&&", tree->expr, 3) == 0)))
				return ;
		}
		parser_tree_order(tree->right, &cmd);
	}
	else
		parser_tree_order(tree->right, pcmd);
}
