/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:46:49 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/18 17:27:56 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_ptree	*parser_expr(t_tokenlst **lst)
{
	t_ptree		*root;
	t_tokenlst	*ntoken;

	ntoken = tokenizer_list_get_node(lst);
	root = parser_tree_create_node(P_EXPR, ntoken->str);
	tokenizer_list_free_node(ntoken);
	return (root);
}

static t_ptree	*parser_redirection(t_tokenlst **lst)
{
	t_ptree		*root;
	t_tokenlst	*rtoken;

	rtoken = tokenizer_list_get_node(lst);
	if (*lst != NULL && (*lst)->type <= T_TAB)
	{
		root = parser_tree_create_node(P_REDIRECTION, rtoken->str);
		root->left = parser_expr(lst);
		tokenizer_list_free_node(rtoken);
		return (root);
	}
	tokenizer_list_free_node(rtoken);
	return (NULL);
}

static t_ptree	*parser_state(t_tokenlst **lst)
{
	t_ptree	*root;

	if (parser_utils_check_type(P_STATE, *lst))
	{
		root = parser_tree_create_node(P_STATE, NULL);
		if ((*lst)->type <= T_TAB)
			root->left = parser_expr(lst);
		else
			root->left = parser_redirection(lst);
		if (root->left == NULL)
			return (parser_tree_all_free(root));
		if (parser_utils_check_type(P_STATE, *lst))
		{
			root->right = parser_state(lst);
			if (root->right == NULL)
				return (parser_tree_all_free(root));
		}
		return (root);
	}
	return (NULL);
}

static t_ptree	*parser_subcmd(t_tokenlst **lst)
{
	t_ptree	*root;

	if (*lst == NULL)
		return (NULL);
	root = parser_tree_create_node(P_SUBCMD, NULL);
	root->left = parser_state(lst);
	if (root->left == NULL)
		return (parser_tree_all_free(root));
	if (*lst != NULL && (*lst)->type == T_PIPE)
	{
		tokenizer_list_free_node(tokenizer_list_get_node(lst));
		root->right = parser_subcmd(lst);
		if (root->right == NULL)
			return (parser_tree_all_free(root));
	}
	return (root);
}

t_ptree	*parser_cmd(t_tokenlst **lst)
{
	t_ptree		*root;

	if (*lst == NULL)
		return (NULL);
	root = parser_tree_create_node(P_CMD, NULL);
	if ((*lst)->type == T_LPARE)
	{
		tokenizer_list_free_node(tokenizer_list_get_node(lst));
		root->left = parser_cmd(lst);
		if (root->left == NULL || *lst == NULL || (*lst)->type != T_RPARE)
			return (parser_tree_all_free(root));
		tokenizer_list_free_node(tokenizer_list_get_node(lst));
	}
	else
		root->left = parser_subcmd(lst);
	if (root->left == NULL)
		return (parser_tree_all_free(root));
	if (parser_utils_check_type(P_CMD, *lst))
	{
		root->expr = parser_utils_get_node_str(tokenizer_list_get_node(lst));
		root->right = parser_cmd(lst);
		if (root->right == NULL)
			return (parser_tree_all_free(root));
	}
	return (root);
}
