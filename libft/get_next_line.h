/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:31:06 by jooh              #+#    #+#             */
/*   Updated: 2023/11/12 21:52:47 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# elif BUFFER_SIZE < 1
#  error "Right BUFFER SIZE PLZ"
# endif

typedef struct s_lst
{
	int				fdnbr;
	char			*save_char;
	size_t			len;
	size_t			mul;
	struct s_lst	*next;
}	t_lst;

char	*get_next_line(int fd);
t_lst	*add_new_back(t_lst **info, int fd);
int		check_endl(t_lst *p);
char	*split_by_endl(t_lst *p, t_lst **info);
void	theleftstr(t_lst *p, t_lst **info);
char	*mem_and_read(t_lst *p, t_lst **info);
char	*ft_realloc(t_lst *p, t_lst **info);
void	del_lst(t_lst *p, t_lst **info);
char	*check_whatread(t_lst *p, t_lst **info, int n);
char	*read_over(t_lst *p, t_lst **info);

#endif