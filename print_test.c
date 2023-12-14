/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:49:50 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/13 22:15:33 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_tree(t_ptree *tree, int flag)
{
	if (flag == 0)
		printf("\n===================== tree =======================\n");
	if (tree != NULL)
	{
		print_parser_tree(tree->left, 1);
		printf("Type : %d, Expr : %s\n", tree->type, tree->expr);
		print_parser_tree(tree->right, 1);
	}
}

void	print_token_list(t_tokenlst *list)
{
	printf("\n================== token list ===================\n");
	while (list != NULL)
	{
		printf("Type : %d, Str : %s\n", list->type, list->str);
		list = list->next;
	}
}

void	print_command_list(t_command *list)
{
	int	idx;

	printf("\n================ command list ==================\n");
	while (list != NULL)
	{
		idx = -1;
		while (list->exprs != NULL && list->exprs[++idx] != NULL)
			printf("Exprs[%d] : %s\n", idx, list->exprs[idx]);
		idx = -1;
		while (list->infiles != NULL && list->infiles[++idx] != NULL)
		{
			if (idx % 2 == 0)
				printf("Inflag[%d] : %d\n", idx / 2, list->inflag[idx / 2]);
			printf("Infiles[%d] : %s\n", idx, list->infiles[idx]);
		}
		idx = -1;
		while (list->outfiles != NULL && list->outfiles[++idx] != NULL)
			printf("Outfiles[%d] : %s\n", idx, list->outfiles[idx]);
		printf("\n");
		list = list->next;
	}
}
