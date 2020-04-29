/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funnel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:33:38 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/13 18:36:50 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int				undefined(t_flag *f)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2};
	char		c[2];

	f->flag[0] = 0;
	if (f->flag_char == 0)
	{
		f->count = 0;
		return (f->count);
	}
	c[0] = f->flag_char;
	c[1] = '\0';
	f->final_arg = c;
	apply_mask(f, mask);
	return (last_modif_c(f));
}

void			init_functions(t_spec *spec)
{
	spec[0].c = 'c';
	spec[0].function = &flag_c;
	spec[1].c = 's';
	spec[1].function = &flag_s;
	spec[2].c = 'p';
	spec[2].function = &flag_p;
	spec[3].c = 'd';
	spec[3].function = &flag_d;
	spec[4].c = 'i';
	spec[4].function = &flag_d;
	spec[5].c = 'u';
	spec[5].function = &flag_u_o;
	spec[6].c = 'o';
	spec[6].function = &flag_u_o;
	spec[7].c = 'x';
	spec[7].function = &flag_x;
	spec[8].c = 'X';
	spec[8].function = &flag_x;
	spec[9].c = 'f';
	spec[9].function = &flag_f;
}

int				funnel(t_flag *f, va_list *list)
{
	t_spec		spec[11];
	int			i;

	if (check(f) == -1)
		return (-1);
	init_functions(spec);
	i = 0;
	f->final_arg = NULL;
	f->flag_char = f->str[f->index];
	while (spec[i].c != f->flag_char && spec[i].c != 0)
		i++;
	if (spec[i].c == 0)
		return (undefined(f));
	return (spec[i].function(f, list));
}
