/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 10:39:46 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 10:39:47 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void			sharp(t_flag *f)
{
	if ((f->flag[2] == 1 && f->final_arg[0] != '0' && f->flag[0] != -1)
			|| f->flag_char == 'p')
	{
		if (f->flag_char == 'o' || f->flag_char == 'x' || f->flag_char == 'X'
				|| f->flag_char == 'p')
		{
			if ((f->flag_char == 'x' && f->final_arg[0] != '0') ||
					f->flag_char == 'p')
			{
				buf('0', f);
				buf('x', f);
			}
			else if (f->flag_char == 'X' && f->final_arg[0] != '0')
			{
				buf('0', f);
				buf('X', f);
			}
			else if ((f->flag_char == 'o') &&
					(size_t)f->flag[0] <= ft_strlen(f->final_arg))
				buf('0', f);
			else if ((f->flag_char == 'o') && f->flag[0] == -1)
				buf('0', f);
		}
	}
}

void			space_plus_sharp(t_flag *f)
{
	if (f->flag[5] == 1 || f->flag[6] == 1)
	{
		if (f->flag_char == 'd' || f->flag_char == 'f' || f->flag_char == 'i')
		{
			if (f->flag[6] == 1 && f->flag[5] == 0 && f->sign != '-')
				buf(' ', f);
			if (f->flag[5] == 1 && (f->sign == '+'))
				buf('+', f);
		}
	}
	if (f->sign == '-')
		buf('-', f);
	sharp(f);
}

void			precision_numb(t_flag *f, int len_zero, int led)
{
	f->len = ft_strlen(f->final_arg);
	if ((f->flag[5] == 1 || f->flag[6] == 1 || f->sign == '-') ||
		(f->flag[2] == 1 && f->flag[0] <= f->len && (f->flag_char == 'o') &&
			f->final_arg[0] != '0') || (f->flag_char == 'u' && f->flag[6] == 1))
	{
		len_zero--;
		if (f->flag_char == 'u' && (f->flag[5] == 1 || f->flag[3] == 1
			|| f->flag[6] == 1))
			len_zero++;
	}
	if (f->flag[2] == 1 && (((f->flag_char == 'x' || f->flag_char == 'X') &&
		f->final_arg[0] != '0' && f->flag[0] != -1) || f->flag_char == 'p'))
		len_zero = len_zero - 2;
	while (f->flag[0] > f->len++)
		len_zero--;
	if (f->flag[0] < f->flag[1] + (int)ft_strlen(f->final_arg))
	{
		while (len_zero-- > 0)
		{
			if (f->flag[3] == 1 && f->flag[0] <= 0 && led)
				buf('0', f);
			else
				buf(' ', f);
		}
	}
}

void			precision_without_width(t_flag *f)
{
	int			len;
	int			prec;

	prec = f->flag[0];
	len = ft_strlen(f->final_arg);
	space_plus_sharp(f);
	while (prec > len-- && len > 0)
		prec--;
	if ((size_t)f->flag[0] > (size_t)f->flag[1] + ft_strlen(f->final_arg))
	{
		while (++len < prec)
			buf('0', f);
	}
}
