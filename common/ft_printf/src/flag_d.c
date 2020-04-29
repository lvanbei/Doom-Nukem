/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 10:59:42 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 11:00:21 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char			*modifier_type(t_flag *f, va_list *list)
{
	intmax_t	data;
	uintmax_t	data_max;

	data = 0;
	if (f->flag[7] == 1)
		data = (intmax_t)((char)va_arg(*list, int));
	else if (f->flag[8] == 1)
		data = (intmax_t)((short)va_arg(*list, int));
	else if (f->flag[9])
		data = (intmax_t)(va_arg(*list, long long));
	else if (f->flag[10])
		data = (intmax_t)(va_arg(*list, long));
	else if (f->flag_char == 'd' || f->flag_char == 'i')
		data = (intmax_t)(va_arg(*list, int));
	data_max = ft_sign(data, f);
	return (ft_itoa_base(data_max, 10, f));
}

int				flag_d(t_flag *f, va_list *list)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	apply_mask(f, mask);
	f->final_arg = modifier_type(f, list);
	last_modif_numb(f);
	return (0);
}
