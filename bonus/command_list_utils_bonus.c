/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:55:01 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/18 17:26:57 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	command_list_free_strs(char **strs)
{
	int	idx;

	idx = 0;
	while (strs != NULL && strs[idx] != NULL)
	{
		free(strs[idx]);
		idx++;
	}
	free(strs);
}

static char	**command_list_append_strs(char **strs, char *expr)
{
	char	**exprs;
	int		len;
	int		idx;

	len = 0;
	while (strs != NULL && strs[len] != NULL)
		len++;
	exprs = ft_calloc(len + 2, sizeof(char *));
	idx = 0;
	while (idx < len)
	{
		exprs[idx] = ft_strdup(strs[idx]);
		idx++;
	}
	exprs[idx] = ft_strdup(expr);
	command_list_free_strs(strs);
	return (exprs);
}

void	command_list_add_expr(t_command **list, char *expr)
{
	t_command	*node;

	node = *list;
	if (node == NULL)
		return ;
	while (node->next != NULL)
		node = node->next;
	if (node->type == C_CMD)
		node->exprs = command_list_append_strs(node->exprs, expr);
	else if (node->type == C_INPUT || node->type == C_HEREDOC)
		node->infiles = command_list_append_strs(node->infiles, expr);
	else
		node->outfiles = command_list_append_strs(node->outfiles, expr);
	node->type = C_CMD;
}

static int	*command_list_append_inflag(char **strs, int *in)
{
	int		*inflag;
	int		len;
	int		idx;

	len = 0;
	while (strs != NULL && strs[len] != NULL)
		len++;
	len /= 2;
	inflag = ft_calloc(len + 1, sizeof(int));
	idx = 0;
	while (idx < len)
	{
		inflag[idx] = in[idx];
		idx++;
	}
	inflag[idx] = 0;
	free(in);
	return (inflag);
}

void	command_list_add_redirection(t_command **list, char *expr)
{
	t_command	*node;

	node = *list;
	if (node == NULL)
		return ;
	while (node->next != NULL)
		node = node->next;
	if (ft_strncmp(expr, "<", 2) == 0)
		node->type = C_INPUT;
	else if (ft_strncmp(expr, ">", 2) == 0)
		node->type = C_OUTPUT;
	else if (ft_strncmp(expr, "<<", 3) == 0)
		node->type = C_HEREDOC;
	else
		node->type = C_APPEND;
	if (node->type == C_INPUT || node->type == C_HEREDOC)
	{
		node->inflag = command_list_append_inflag(node->infiles, node->inflag);
		node->infiles = command_list_append_strs(node->infiles, expr);
	}
	else
		node->outfiles = command_list_append_strs(node->outfiles, expr);
}
