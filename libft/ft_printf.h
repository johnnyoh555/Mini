/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:46:16 by jooh              #+#    #+#             */
/*   Updated: 2023/11/22 16:01:36 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_info
{
	int		flag_ze;
	int		flag_mi;
	int		flag_pl;
	int		flag_sh;
	int		flag_sp;
	int		wid;
	int		pre;
	char	format;
	int		ret;
	int		len;
	int		minus;
	int		add;
}	t_info;

int		ft_printf(const char *s, ...);
int		while_str(const char **s, t_info *info);
void	reset_info(t_info *info);
void	if_percent(const char **s, va_list *ap, t_info *info);
void	check_flag(const char **s, t_info *info);
int		check_pre_or_wid(const char **s);
void	watershed(va_list *ap, t_info *info);
void	ft_write(t_info *info, char *str, int len);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
void	format_di(va_list *ap, t_info *info);
void	format_di_me(t_info *info, char *nbrstr, int size);
void	format_di_nopre(t_info *info, char *s2, char *s1, int size);
void	format_di_pre(t_info *info, char *s2, char *s1, int i);
void	format_else(t_info *info);
void	format_c(va_list *ap, t_info *info);
void	print_format_c(int i, char *str, t_info *info);
void	format_s(va_list *ap, t_info *info);
void	print_format_s(char *str, t_info *info, int len);
void	format_p(va_list *ap, t_info *info);
void	format_p_me(t_info *info, char *nbrstr, int size);
void	format_p_nopre(t_info *info, char *nbrstr, char *str, int size);
void	format_p_pre(t_info *info, char *nbrstr, char *str, int size);
void	format_u(va_list *ap, t_info *info);
void	format_u_me(t_info *info, char *nbrstr, int size);
void	format_u_nopre(t_info *info, char *nbrstr, char *str, int size);
void	format_u_pre(t_info *info, char *nbrstr, char *str, int size);
void	format_x(va_list *ap, t_info *info);
void	format_x_me(t_info *info, char *nbrstr, int size);
void	format_x_nopre(t_info *info, char *s2, char *s1, int i);
void	format_x_pre(t_info *info, char *s2, char *s1, int i);
char	*ft_convert(unsigned long long n, char *base);
char	*ft_itoa(long n);

#endif