/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:07:38 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 11:07:39 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int				get_num(t_flag *f)
{
	int			i;
	char		*str;

	i = f->index;
	while (ft_isdigit(f->str[f->index]))
		f->index++;
	str = ft_strsub(f->str, i, f->index - i);
	free(str);
	return (ft_atoi(str));
}

void			init_f(t_flag *f)
{
	int			i;

	i = -1;
	while (++i < FLAG_NUM)
		f->flag[i] = 0;
	f->index = 0;
}

void			check_f(t_flag *f)
{
	if (f->str[f->index] == '#' || f->str[f->index] == '0'
			|| f->str[f->index] == '-' || f->str[f->index] == '+'
			|| f->str[f->index] == ' ')
	{
		if (f->str[f->index] == '#')
			f->flag[2] = 1;
		if (f->str[f->index] == '0')
			f->flag[3] = 1;
		if (f->str[f->index] == '-')
			f->flag[4] = 1;
		if (f->str[f->index] == '+')
			f->flag[5] = 1;
		if (f->str[f->index] == ' ')
			f->flag[6] = 1;
		f->index++;
	}
}
