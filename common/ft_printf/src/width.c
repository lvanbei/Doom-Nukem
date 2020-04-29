/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 10:29:39 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 10:29:40 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void			zero_numb(t_flag *f)
{
	f->i = -1;
	f->len = ft_strlen(f->final_arg);
	f->len_zero = f->flag[1] - f->len;
	if (f->flag[3] == 1 && f->flag[0] <= 0)
	{
		if (f->check_prec == 1)
		{
			precision_numb(f, f->len_zero, 0);
			space_plus_sharp(f);
		}
		else
		{
			space_plus_sharp(f);
			precision_numb(f, f->len_zero, 1);
		}
	}
	else
	{
		precision_numb(f, f->len_zero, 1);
		space_plus_sharp(f);
	}
	while (f->flag[0] > f->len++)
		buf('0', f);
	while (f->final_arg[++f->i] != '\0')
		buf(f->final_arg[f->i], f);
}

void			minus_numb(t_flag *f)
{
	int			i;
	int			len;
	int			len_zero;

	i = -1;
	len_zero = f->flag[1] - (int)ft_strlen(f->final_arg);
	len = (int)ft_strlen(f->final_arg);
	f->flag[3] = 0;
	space_plus_sharp(f);
	while (f->flag[0] > len++)
		buf('0', f);
	while (f->final_arg[++i] != '\0')
		buf(f->final_arg[i], f);
	precision_numb(f, len_zero, 1);
}

void			width_numb(t_flag *f)
{
	int			i;
	int			len;

	i = -1;
	len = (int)ft_strlen(f->final_arg);
	if (len < f->flag[1])
	{
		if (f->flag[4] == 1)
			minus_numb(f);
		else
			zero_numb(f);
	}
	else
	{
		space_plus_sharp(f);
		while (f->flag[0] > len++)
			buf('0', f);
		while (f->final_arg[++i] != '\0')
			buf(f->final_arg[i], f);
	}
}
