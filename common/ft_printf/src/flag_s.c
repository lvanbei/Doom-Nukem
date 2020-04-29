/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:53:16 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/13 18:54:31 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void			precision_str(t_flag *f)
{
	if (f->flag[0] == -1)
		f->final_arg = "\0";
	else if (f->flag_char == 's')
		f->final_arg = ft_strsub(f->final_arg, 0, f->flag[0]);
}

void			display_arg(t_flag *f)
{
	int			i;

	i = -1;
	if (f->final_arg == NULL)
		buf_null(f);
	else
	{
		while (f->final_arg[++i] != '\0')
			buf(f->final_arg[i], f);
	}
	end(f);
}

int				flag_s(t_flag *f, va_list *list)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2};

	apply_mask(f, mask);
	f->final_arg = va_arg(*list, char*);
	if (f->final_arg == NULL)
		f->final_arg = "(null)";
	last_modif_c(f);
	return (0);
}
