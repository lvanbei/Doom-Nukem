/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:45:44 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/13 18:47:47 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*modifier_x(t_flag *f, va_list *list)
{
	intmax_t data;

	if (f->flag[7] == 1)
		data = (uintmax_t)((unsigned char)va_arg(*list, unsigned int));
	else if (f->flag[8] == 1)
		data = (uintmax_t)((unsigned short)va_arg(*list, unsigned int));
	else if (f->flag[9] == 1)
		data = (uintmax_t)(va_arg(*list, unsigned long long));
	else if (f->flag[10] == 1)
		data = (uintmax_t)(va_arg(*list, unsigned long));
	else
		data = (uintmax_t)va_arg(*list, unsigned int);
	if (f->flag_char == 'X')
		return (ft_itoa_base(data, 16, f));
	if (f->flag_char == 'x')
		return ((ft_itoa_base(data, 16, f)));
	return (NULL);
}

int		flag_x(t_flag *f, va_list *list)
{
	static int	mask[13] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	apply_mask(f, mask);
	f->final_arg = modifier_x(f, list);
	if (f->flag[0] == -1 && f->final_arg[0] != '0' &&
			f->flag[2] == 1 && f->check_prec == 1)
		f->flag[0] = 0;
	last_modif_numb(f);
	return (0);
}
