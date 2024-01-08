/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_list_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:51:34 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/26 14:22:28 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_tokenlst	*tokenizer_list_create_node(int type, char *str)
{
	t_tokenlst	*node;

	node = ft_calloc(1, sizeof(t_tokenlst));
	node->type = type;
	node->str = str;
	node->next = NULL;
	return (node);
}

void	tokenizer_list_add_node(t_tokenlst **list, t_tokenlst *node)
{
	t_tokenlst	*tmp;

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

t_tokenlst	*tokenizer_list_get_node(t_tokenlst **list)
{
	t_tokenlst	*tmp;

	if (*list == NULL)
		return (NULL);
	tmp = *list;
	*list = (*list)->next;
	return (tmp);
}

void	tokenizer_list_free_node(t_tokenlst *node)
{
	if (node != NULL)
	{
		free(node->str);
		free(node);
	}
}

void	*tokenizer_list_all_free(t_tokenlst **list)
{
	t_tokenlst	*tmp;

	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		tokenizer_list_free_node(tmp);
	}
	return (NULL);
}
