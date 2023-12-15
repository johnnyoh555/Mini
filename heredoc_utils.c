/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:31:06 by sungyoon          #+#    #+#             */
/*   Updated: 2023/12/15 16:11:18 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*delete_quote(char *s)
{
	char	*str;
	int		idx;
	int		size;

	idx = 0;
	size = 0;
	while (s[idx] != '\0')
	{
		if (!((s[idx] == '\"' || s[idx] == '\'') && \
			(idx == 0 || s[idx - 1] != '\\')))
			size++;
		idx++;
	}
	str = ft_calloc(size + 1, sizeof(char));
	idx--;
	while (size > 0)
	{
		if (!((s[idx] == '\"' || s[idx] == '\'') && \
			(idx == 0 || s[idx - 1] != '\\')))
			str[--size] = s[idx];
		idx--;
	}
	return (str);
}

static char	*delete_backslash(char *s)
{
	char	*str;
	int		idx;
	int		size;

	idx = 0;
	size = 0;
	while (s[idx] != '\0')
	{
		if (s[idx] != '\\')
			size++;
		idx++;
	}
	str = ft_calloc(size + 1, sizeof(char));
	idx--;
	while (size > 0)
	{
		if (s[idx] != '\\')
			str[--size] = s[idx];
		idx--;
	}
	return (str);
}

int	get_str_max_length(char *s1, char *s2)
{
	int	s1_len;
	int	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len > s2_len)
		return (s1_len);
	else
		return (s2_len);
}

char	*make_heredoc_file_name(void)
{
	char	*str;
	char	*strnbr;
	int		nbr;

	nbr = 0;
	strnbr = ft_itoa(nbr);
	str = ft_strjoin("./heredoc/heredoc", strnbr);
	while (access(str, F_OK) == 0)
	{
		free(str);
		free(strnbr);
		nbr++;
		strnbr = ft_itoa(nbr);
		str = ft_strjoin("./heredoc/heredoc", strnbr);
	}
	free(strnbr);
	return (str);
}

char	*make_limiter(t_command *cmd, int idx)
{
	char	*limiter;
	char	*tmp;

	if (!(ft_strchr(cmd->infiles[idx + 1], '\'') || \
		ft_strchr(cmd->infiles[idx + 1], '\"')))
		cmd->inflag[idx / 2] = 1;
	tmp = delete_quote(cmd->infiles[idx + 1]);
	limiter = delete_backslash(tmp);
	free(tmp);
	return (limiter);
}
