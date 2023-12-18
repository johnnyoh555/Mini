/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:28:58 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/18 11:26:12 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(t_command *command, t_info *info)
{
	int		i;
	int		j;

	info->cmd = 0;
	while (command)
	{
		command = command->next;
		info->cmd++;
	}
	i = 0;
	info->path = 0;
	while ((info->envp)[i])
	{
		j = -1;
		if (!ft_strncmp("PATH=", (info->envp)[i], 5))
		{
			info->path = ft_split((info->envp)[i] + 5, ':');
			break ;
		}
		i++;
	}
}

int	excute_cmd(t_command *cmd, t_info *info)
{
	int	ret;

	init_info(cmd, info);
	if (extend_env(cmd, info))
	{
		end_seq(info);
		return (1);
	}
	ret = execute(cmd, info);
	end_seq(info);
	return (ret);
}

int	parser_tree_excutable(t_ptree *tree, t_command *cmd, t_info *info)
{
	int	ret;

	ret = 0;
	if (cmd != NULL)
	{
		ret = excute_cmd(cmd, info);
		command_list_all_free(cmd);
		if (tree->expr != NULL && \
			ret != 0 && !ft_strncmp("||", tree->expr, 3))
			ret = 0;
	}
	return (ret);
}

int	parser_tree_left_search(t_ptree *tree, t_command **cmd, t_info *info)
{
	int	ret;

	ret = 0;
	if (tree->type == P_SUBCMD)
		command_list_add_node(cmd, command_list_create_node());
	else if (tree->type == P_REDIRECTION)
		command_list_add_redirection(cmd, tree->expr);
	else if (tree->type == P_EXPR)
		command_list_add_expr(cmd, tree->expr);
	ret = parser_tree_order(tree->left, cmd, info);
	return (ret);
}

int	parser_tree_order(t_ptree *tree, t_command **pcmd, t_info *info)
{
	t_command	*cmd;
	int			ret;

	cmd = NULL;
	ret = 0;
	if (tree == NULL)
		return (0);
	if (tree->type == P_CMD)
		ret = parser_tree_left_search(tree, &cmd, info);
	else
		ret = parser_tree_left_search(tree, pcmd, info);
	if (ret != 0)
		return (ret);
	if (tree->type == P_CMD)
	{
		ret = parser_tree_excutable(tree, cmd, info);
		if (ret != 0)
			return (ret);
		ret = parser_tree_order(tree->right, &cmd, info);
	}
	else
		ret = parser_tree_order(tree->right, pcmd, info);
	return (ret);
}
