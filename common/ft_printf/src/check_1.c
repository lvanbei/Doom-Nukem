/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:54:45 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 11:06:24 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void			check_width(t_flag *f)
{
	if (ft_isdigit(f->str[f->index]) && f->str[f->index] != '0')
		f->flag[1] = get_num(f);
}

void			check_precision(t_flag *f)
{
	int i;

	i = 0;
	if (f->str[f->index] == '.')
	{
		f->check_prec = 1;
		f->flag[0] = 0;
		i = ++f->index;
		f->flag[0] = get_num(f);
		if (f->flag[0] == 0)
			f->flag[0] = -1;
	}
	(void)i;
}

void			check_spec(t_flag *f)
{
	while (f->str[f->index] == 'h'
			|| f->str[f->index] == 'l' || f->str[f->index] == 'L'
			|| f->str[f->index] == 'z')
	{
		if (f->str[f->index] == 'h' && f->str[f->index + 1] == 'h')
		{
			f->flag[7] = 1;
			f->index++;
		}
		else if (f->str[f->index] == 'h')
			f->flag[8] = 1;
		if (f->str[f->index] == 'l' && f->str[f->index + 1] == 'l')
		{
			f->flag[9] = 1;
			f->index++;
		}
		else if (f->str[f->index] == 'l')
			f->flag[10] = 1;
		if (f->str[f->index] == 'L')
			f->flag[11] = 1;
		f->index++;
	}
}

int				check(t_flag *f)
{
	init_f(f);
	while (f->str[f->index] == '#' || f->str[f->index] == '0'
			|| f->str[f->index] == '-' || f->str[f->index] == '+'
			|| f->str[f->index] == ' ' || f->str[f->index] == 'h'
			|| f->str[f->index] == 'l' || f->str[f->index] == 'L'
			|| f->str[f->index] == 'z' || f->str[f->index] == '.'
			|| ft_isdigit(f->str[f->index]))
	{
		check_f(f);
		check_width(f);
		check_precision(f);
		check_spec(f);
	}
	if ((size_t)f->index == ft_strlen(f->str))
		return (-1);
	return (0);
}
