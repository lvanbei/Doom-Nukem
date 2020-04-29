/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:54:43 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/13 19:02:09 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int				last_modif_numb(t_flag *f)
{
	int			i;

	i = -1;
	if (f->flag[0] == -1 && f->final_arg[0] == '0' && !(f->flag[2] == 1 &&
				(f->flag_char == 'o' || f->flag_char == 'p')))
		f->final_arg = "\0";
	if (f->flag[1] > 0)
		width_numb(f);
	else if (f->flag[1] == 0 && f->flag[0] > 0)
		precision_without_width(f);
	if (f->flag[0] <= 0 && f->flag[1] == 0)
		space_plus_sharp(f);
	while (f->final_arg[++i] != '\0' && f->flag[1] == 0)
		buf(f->final_arg[i], f);
	end(f);
	return (1);
}

int				flag_p(t_flag *f, va_list *list)
{
	static int	mask[13] = {0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2};

	f->flag[2] = 1;
	apply_mask(f, mask);
	f->final_arg = ft_tolower_str(ft_itoa_base((uintmax_t)
	va_arg(*list, void *), 16, f));
	if (f->flag[0] == -1 && f->final_arg[0] == '0')
	{
		if (f->flag[1] != -1 && f->flag[4] == -1)
			precision_numb(f, f->flag[1], 1);
		if (f->flag[1] != -1 && f->flag[4] != -1)
		{
			f->final_arg = "\0";
			return (last_modif_numb(f));
		}
		buf('0', f);
		buf('x', f);
	}
	else
		last_modif_numb(f);
	return (0);
}
