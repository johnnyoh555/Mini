/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:21:10 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/26 14:22:28 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_command	*command_list_create_node(void)
{
	t_command	*node;

	node = ft_calloc(1, sizeof(t_command));
	node->type = 0;
	node->exprs = NULL;
	node->infiles = NULL;
	node->outfiles = NULL;
	node->inflag = NULL;
	node->file_cnt = 0;
	node->file_flag = NULL;
	node->next = NULL;
	return (node);
}

void	command_list_add_node(t_command **list, t_command *node)
{
	t_command	*tmp;

	if (*list == NULL)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_command	*command_list_get_node(t_command **list)
{
	t_command	*tmp;

	if (*list == NULL)
		return (NULL);
	tmp = *list;
	*list = (*list)->next;
	return (tmp);
}

void	command_list_free_node(t_command *node)
{
	command_list_free_strs(node->exprs);
	command_list_free_strs(node->infiles);
	command_list_free_strs(node->outfiles);
	free(node->inflag);
	free(node->file_flag);
	free(node);
}

void	command_list_all_free(t_command *list)
{
	t_command	*tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		command_list_free_node(tmp);
	}
}
