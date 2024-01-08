/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:15:18 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/26 14:22:28 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	tokenizer_ischarset(char *str)
{
	const char	*charset = " \t\n;()|&<>";
	int			idx;

	idx = 0;
	while (charset[idx] != '\0')
	{
		if (charset[idx] == *str)
		{
			if (idx >= 6 && *(str + 1) == charset[idx])
				return (idx + 4);
			return (idx);
		}
		idx++;
	}
	return (-1);
}

static int	tokenizer_check_quote(int idx, char *str, int flag)
{
	if ((idx == 0 || (idx > 0 && str[idx - 1] != '\\')))
	{
		if (str[idx] == '\'' && (flag & E_ALL_QUOTE) == 0)
			flag |= E_QUOTE;
		else if (str[idx] == '\"' && (flag & E_ALL_QUOTE) == 0)
			flag |= E_DOUBLE_QUOTE;
		else if (str[idx] == '\'' && (flag & E_QUOTE) != 0)
			flag &= ~(E_QUOTE);
		else if (str[idx] == '\"' && (flag & E_DOUBLE_QUOTE) != 0)
			flag &= ~(E_DOUBLE_QUOTE);
	}
	return (flag);
}

static int	tokenizer_get_word(t_tokenlst **lst, char *str, int *pos, int *idx)
{
	int			type;
	int			sep;

	sep = *idx;
	type = tokenizer_ischarset(&str[*idx]);
	if (type == -1)
		return (1);
	if (*pos != *idx)
		tokenizer_list_add_node(lst, \
		tokenizer_list_create_node(T_SPA, ft_substr(str, *pos, *idx - *pos)));
	if (type >= T_OR)
		*idx = *idx + 1;
	*pos = *idx + 1;
	if (type > T_TAB)
		tokenizer_list_add_node(lst, \
		tokenizer_list_create_node(type, ft_substr(str, sep, *idx - sep + 1)));
	return (0);
}

static int	tokenizer_error(int flag)
{
	if ((flag & E_QUOTE) == E_QUOTE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("unexpected EOF while looking for matching `''", 2);
	}
	else if ((flag & E_DOUBLE_QUOTE) == E_DOUBLE_QUOTE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("unexpected EOF while looking for matching `\"'", 2);
	}
	else
		return (0);
	return (1);
}

t_tokenlst	*tokenizer_parse(char *str, int *flag)
{
	t_tokenlst	*lst;
	int			idx;
	int			pos;

	lst = NULL;
	pos = 0;
	idx = 0;
	*flag = 0;
	while (str[idx] != '\0')
	{
		*flag = tokenizer_check_quote(idx, str, *flag);
		if (*flag == 0)
			tokenizer_get_word(&lst, str, &pos, &idx);
		idx++;
	}
	if (tokenizer_error(*flag))
		return (tokenizer_list_all_free(&lst));
	else if (idx != pos)
		tokenizer_list_add_node(&lst, \
		tokenizer_list_create_node(T_SPA, ft_strdup(&str[pos])));
	return (lst);
}
