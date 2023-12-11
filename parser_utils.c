/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:36:09 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/11 18:24:42 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_utils_check_type(int type, t_tokenlst *node)
{
	if (node == NULL)
		return (0);
	if (type == P_EXPR && node->type <= T_TAB)
		return (1);
	else if (type == P_STATE && (node->type <= T_TAB || \
			node->type == T_APPEND || node->type == T_HEREDOC || \
			node->type == T_LESS || node->type == T_GREATER))
		return (1);
	else if (type == P_CMD && (node->type == T_LPARE || \
			(T_OR <= node->type && node->type <= T_AND)))
		return (1);
	return (0);
}

char	*parser_utils_get_node_str(t_tokenlst *node)
{
	char	*str;

	str = ft_strdup(node->str);
	tokenizer_list_free_node(node);
	return (str);
}

int	parser_error(t_ptree *tree, t_tokenlst *list)
{
	const char	*token = " \t\n;()|&<>";

	if (tree == NULL)
	{
		if (list != NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token '", 2);
			if (token[list->type] == '\n')
				ft_putstr_fd("newline", 2);
			else
				ft_putchar_fd(token[list->type], 2);
			ft_putendl_fd("'", 2);
			tokenizer_list_all_free(&list);
		}
		else
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putendl_fd("syntax error: unexpected end of file", 2);
		}
		return (1);
	}
	return (0);
}
