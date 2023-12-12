/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:26:58 by jooh              #+#    #+#             */
/*   Updated: 2023/11/12 21:53:12 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	del_lst(t_lst *p, t_lst **info)
{
	t_lst	*newlst;

	newlst = *info;
	if (p == newlst)
	{
		*info = newlst->next;
		free(p);
	}
	else
	{
		while (newlst->next != p)
			newlst = newlst->next;
		newlst->next = p->next;
		free(p);
	}
}

char	*check_whatread(t_lst *p, t_lst **info, int n)
{
	char	*str;
	size_t	i;

	i = -1;
	if (n == 0 && p->len == 0)
	{
		free(p->save_char);
		return (0);
	}
	if (check_endl(p) == 0)
	{
		str = malloc(p->len + 1);
		if (str == 0)
		{
			free(p->save_char);
			return (0);
		}
		while (++i <= p->len)
			str[i] = *(p->save_char + i);
		free(p->save_char);
		del_lst(p, info);
		return (str);
	}
	return (split_by_endl(p, info));
}

char	*read_over(t_lst *p, t_lst **info)
{
	int		n;
	size_t	i;

	i = -1;
	n = BUFFER_SIZE;
	while (n == BUFFER_SIZE && check_endl(p) == 0 && ++i >= 0)
	{
		if (i == (*info)->mul)
		{	
			(*info)->mul *= 2;
			if (ft_realloc(p, info) == 0)
				return (0);
			i = 0;
		}
		n = read(p->fdnbr, p->save_char + p->len, BUFFER_SIZE);
		if (n == -1)
		{
			free(p->save_char);
			return (0);
		}
		p->len += n;
		*(p->save_char + p->len) = 0;
	}
	return (check_whatread(p, info, n));
}

char	*ft_realloc(t_lst *p, t_lst **info)
{
	char	*str;
	char	*newstr;
	size_t	i;

	str = p->save_char;
	newstr = malloc(p->len + (BUFFER_SIZE * (*info)->mul) + 1);
	if (newstr == 0)
	{
		free(str);
		return (0);
	}
	i = 0;
	while (i <= p->len)
	{
		*(newstr + i) = *(str + i);
		i++;
	}
	p->save_char = newstr;
	free(str);
	return (newstr);
}

char	*mem_and_read(t_lst *p, t_lst **info)
{
	char	*str;

	(*info)->mul = 1;
	if (p->save_char == 0)
	{
		p->save_char = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (p->save_char == 0)
			return (0);
	}
	else
	{
		if (ft_realloc(p, info) == 0)
			return (0);
	}
	str = read_over(p, info);
	return (str);
}
