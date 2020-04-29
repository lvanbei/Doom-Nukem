/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:28:29 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/13 18:28:30 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		end(t_flag *f)
{
	if (f->flag[0] >= 0 && f->final_arg != NULL && f->final_arg[0] != '\0' &&
		f->final_arg[0] != '0')
	{
		if (f->flag_char == 'x' || f->flag_char == 'X' || f->flag_char == 'o'
		|| f->flag_char == 'u' || f->flag_char == 'f' || f->flag_char == 'd'
		|| f->flag_char == 'D' || f->flag_char == 'p' || f->flag_char == 'i'
		|| (f->flag_char == 's' && (size_t)f->flag[0] < ft_strlen(f->final_arg)
		&& f->flag[0] > 0))
			free(f->final_arg);
	}
}

int			ft_printf(const char *restrict format, ...)
{
	va_list list;
	int		i;
	t_flag	f;

	i = -1;
	f.count = 0;
	f.check_prec = 0;
	f.g_i = 0;
	va_start(list, format);
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			f.str = (char*)&format[++i];
			if (funnel(&f, &list) == -1)
				break ;
			i += f.index;
		}
		else if (format[i] != '\0' && format[i] != '%')
			buf(format[i], &f);
	}
	if (f.g_i > 0)
		display(&f);
	va_end(list);
	return (f.count);
}

int			ft_vprintf(const char *format, va_list ap)
{
	int		i;
	t_flag	f;
	va_list *ap2;

	ap2 = (va_list*)ap;
	i = -1;
	f.count = 0;
	f.check_prec = 0;
	f.g_i = 0;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			f.str = (char*)&format[++i];
			if (funnel(&f, ap2) == -1)
				break ;
			i += f.index;
		}
		else if (format[i] != '\0' && format[i] != '%')
			buf(format[i], &f);
	}
	if (f.g_i > 0)
		display(&f);
	va_end(*ap2);
	return (f.count);
}

int			ft_vsprintf(char *str, const char *format, va_list ap)
{
	int		i;
	t_flag	f;
	va_list *ap2;

	ap2 = (va_list*)ap;
	i = -1;
	f.count = 0;
	f.check_prec = 0;
	f.g_i = 0;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			f.str = (char*)&format[++i];
			if (funnel(&f, ap2) == -1)
				break ;
			i += f.index;
		}
		else if (format[i] != '\0' && format[i] != '%')
			buf(format[i], &f);
	}
	if (f.g_i > 0)
		put_in_char(str, &f);
	va_end(*ap2);
	return (f.count);
}

int			ft_sprintf(char *str, const char *restrict format, ...)
{
	va_list list;
	int		i;
	t_flag	f;

	i = -1;
	f.count = 0;
	f.check_prec = 0;
	f.g_i = 0;
	va_start(list, format);
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			f.str = (char*)&format[++i];
			if (funnel(&f, &list) == -1)
				break ;
			i += f.index;
		}
		else if (format[i] != '\0' && format[i] != '%')
			buf(format[i], &f);
	}
	if (f.g_i > 0)
		put_in_char(str, &f);
	va_end(list);
	return (f.count);
}
