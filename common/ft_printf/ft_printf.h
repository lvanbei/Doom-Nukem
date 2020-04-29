/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:22:42 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 11:22:42 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <math.h>
# include <inttypes.h>
# include <stdlib.h>
# define FLAG_NUM 13

/*
** 	| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
** 	|pre|wid| # | 0 | - | + |   | hh| h | ll|  l |  L |  z |
*/

typedef struct		s_spec
{
	char			c;
	int				(*function)();
}					t_spec;

typedef struct		s_flag
{
	int				index;
	char			*str;
	int				flag[FLAG_NUM];
	char			*final_arg;
	char			flag_char;
	int				count;
	char			sign;
	int				check_prec;
	char			g_buf[4096];
	int				g_i;
	int				len_zero;
	int				i;
	int				len;
}					t_flag;

/*
**    ft_printf.c
*/

int					ft_printf(const char *restrict format, ...);
int					ft_vprintf(const char *format, va_list ap);
int					ft_vsprintf(char *str, const char *format, va_list ap);
int					ft_sprintf(char *str, const char *restrict format, ...);
void				end(t_flag *f);

/*
**    funnel.c
*/

int					funnel(t_flag *f, va_list *list);

/*
**    check_1.c
*/

int					check(t_flag *f);

/*
**    check_2.c
*/

int					get_num(t_flag *f);
void				init_f(t_flag *f);
void				check_f(t_flag *f);

/*
**     flag_c
*/

int					flag_c(t_flag *f, va_list *list);
void				display_arg(t_flag *f);
int					last_modif_c(t_flag *f);

/*
**     flag_s
*/

int					flag_s(t_flag *f, va_list *list);
void				precision_str(t_flag *f);

/*
**     flag_p
*/

int					flag_p(t_flag *f, va_list *list);
int					last_modif_numb(t_flag *f);

/*
**      buff.c
*/

void				buf(char c, t_flag *f);
void				buf_null(t_flag *f);
void				display(t_flag *f);
void				set_buf(t_flag *f);
void				put_in_char(char *str, t_flag *f);

/*
**       tools_1.c
*/

char				*ft_itoa_base(uintmax_t nbr, int base, t_flag *f);
char				*ft_tolower_str(char *str);
uintmax_t			ft_sign(intmax_t nbr, t_flag *f);
void				negative(t_flag *f, double *nbr, int *neg);
void				apply_mask(t_flag *f, int *mask);

/*
**       tools_2.c
*/

size_t				ft_strlen(const char *s);
char				*ft_strcpy(char *dest, const char *src);
int					ft_isdigit(int c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
int					ft_tolower(int word);

/*
**       tools_3.c
*/

int					ft_atoi(const char *str);

/*
**      flag_d
*/

int					flag_d(t_flag *f, va_list *list);

/*
**      flag_u_o
*/

int					flag_u_o(t_flag *f, va_list *list);
char				*modifier_o_u(t_flag *f, va_list *list);

/*
**      flag_x
*/

int					flag_x(t_flag *f, va_list *list);

/*
**      flag_f
*/

int					flag_f(t_flag *f, va_list *list);

/*
**      width.c
*/
void				width_numb(t_flag *f);

/*
**      precision.c
*/

void				precision_numb(t_flag *f, int len_zero, int led);
void				precision_without_width(t_flag *f);
void				space_plus_sharp(t_flag *f);
#endif
