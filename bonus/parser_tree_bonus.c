/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:30:54 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/18 17:28:00 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_ptree	*parser_tree_create_node(int type, char *expr)
{
	t_ptree	*node;

	node = ft_calloc(1, sizeof(t_ptree));
	node->type = type;
	if (expr == NULL)
		node->expr = NULL;
	else
		node->expr = ft_strdup(expr);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	parser_tree_node_free(t_ptree *node)
{
	if (node != NULL)
	{
		free(node->expr);
		free(node);
	}
}

void	*parser_tree_all_free(t_ptree *tree)
{
	if (tree != NULL)
	{
		parser_tree_all_free(tree->left);
		parser_tree_all_free(tree->right);
		parser_tree_node_free(tree);
	}
	return (NULL);
}

t_ptree	*parser_tree_make_root(int type, t_ptree *left, t_ptree *right)
{
	t_ptree	*root;

	root = parser_tree_create_node(type, NULL);
	root->left = left;
	root->right = right;
	return (root);
}
