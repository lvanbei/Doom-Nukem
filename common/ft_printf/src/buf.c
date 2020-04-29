/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:11:53 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/17 11:11:53 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void				set_buf(t_flag *f)
{
	int				n;

	n = 0;
	while (n < 4096)
	{
		f->g_buf[n] = '\0';
		n++;
	}
	f->g_i = 0;
}

void				display(t_flag *f)
{
	f->count += write(1, f->g_buf, f->g_i);
	set_buf(f);
}

void				buf_null(t_flag *f)
{
	static char		str[6] = "(null)";
	int				i;

	i = 0;
	while (str[i] != '\0')
	{
		buf(str[i], f);
		i++;
	}
}

void				buf(char c, t_flag *f)
{
	f->g_buf[f->g_i] = c;
	f->g_i++;
	if (f->g_i == 4096)
		display(f);
}

void				put_in_char(char *str, t_flag *f)
{
	f->count += f->g_i;
	f->g_buf[f->g_i] = '\0';
	str = ft_strcpy(str, f->g_buf);
	set_buf(f);
}
