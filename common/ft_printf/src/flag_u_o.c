/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_u_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:51:51 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/13 18:53:03 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char			*modifier_o_u(t_flag *f, va_list *list)
{
	intmax_t	data;

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
	if (f->flag_char == 'u')
		return (ft_itoa_base(data, 10, f));
	if (f->flag_char == 'o')
		return (ft_itoa_base(data, 8, f));
	return (NULL);
}

int				flag_u_o(t_flag *f, va_list *list)
{
	static int	mask_u[12] = {0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	static int	mask_o[12] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	if (f->flag_char == 'u')
		apply_mask(f, mask_u);
	if (f->flag_char == 'o')
		apply_mask(f, mask_o);
	f->final_arg = modifier_o_u(f, list);
	if (f->flag[0] == -1 && f->final_arg[0] != '0' && f->flag[2] == 1
			&& f->flag_char == 'o')
		f->flag[0] = 0;
	last_modif_numb(f);
	return (0);
}
