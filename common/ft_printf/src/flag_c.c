/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:00:54 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 11:02:23 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void			zero_char(t_flag *f)
{
	int			space_len;

	space_len = f->flag[1] - ft_strlen(f->final_arg);
	if (f->flag_char == 'c' && f->final_arg[0] == 0)
		space_len--;
	while (space_len-- > 0)
	{
		if (f->flag[3] == 1 && f->flag[0] <= 0)
			buf('0', f);
		else
			buf(' ', f);
	}
	display_arg(f);
}

void			minus_char(t_flag *f)
{
	int			space_len;

	space_len = f->flag[1] - ft_strlen(f->final_arg);
	if (f->flag_char == 'c' && f->final_arg[0] == 0)
		space_len--;
	display_arg(f);
	while (space_len-- > 0)
		buf(' ', f);
}

void			width_char(t_flag *f)
{
	int			i;

	i = 0;
	if (f->final_arg)
		i = ft_strlen(f->final_arg);
	if (i < f->flag[1])
	{
		if (f->flag[4] == 1)
			minus_char(f);
		else
			zero_char(f);
	}
	else
		display_arg(f);
}

int				last_modif_c(t_flag *f)
{
	if (f->flag[0] != 0)
		precision_str(f);
	if (f->flag[1] > 0)
		width_char(f);
	if (f->flag[1] == 0)
		display_arg(f);
	return (1);
}

int				flag_c(t_flag *f, va_list *list)
{
	static int	mask_c[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2};
	char		c;
	char		c_final[2];

	apply_mask(f, mask_c);
	c = (char)va_arg(*list, int);
	if (c == 0 && f->flag[0] == -1)
		f->flag[0] = 0;
	c_final[0] = c;
	c_final[1] = '\0';
	f->final_arg = c_final;
	last_modif_c(f);
	if (f->final_arg[0] == 0)
		buf('\0', f);
	return (0);
}
