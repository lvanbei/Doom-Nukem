/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 10:43:24 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/25 09:44:23 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int				infin(t_flag *f)
{
	int			i;
	char		tmp[4];

	i = -1;
	tmp[0] = 'i';
	tmp[1] = 'n';
	tmp[2] = 'f';
	tmp[3] = '\0';
	f->final_arg = tmp;
	while (f->final_arg[++i] != '\0' && f->flag[1] == 0)
		buf(f->final_arg[i], f);
	end(f);
	return (1);
}

double			modulo_f(int *len, double nbr)
{
	double		modulo;

	modulo = 1;
	while ((int)(nbr /= 10) != 0)
	{
		modulo *= 10;
		(*len)++;
	}
	return (modulo);
}

void			find_int(int *i, double *nbr, double modulo, t_flag *f)
{
	while ((int)modulo != 0)
	{
		f->final_arg[(*i)++] = (char)((*nbr / modulo) + 48);
		*nbr -= (int)(*nbr / modulo) * modulo;
		modulo /= 10;
	}
}

void			find_float(int *i, double nbr, t_flag *f)
{
	int			j;
	int			tmp;

	nbr *= 10;
	j = 0;
	f->final_arg[(*i)++] = '.';
	while (j++ <= f->flag[0])
	{
		if ((int)nbr == 0)
		{
			f->final_arg[(*i)++] = '0';
			continue ;
		}
		tmp = ((int)nbr != 9) ? (int)(nbr + 0.01) : (int)nbr;
		f->final_arg[(*i)++] = (char)(tmp + 48);
		nbr = (nbr - tmp) * 10;
	}
}

int				flag_f(t_flag *f, va_list *list)
{
	double		nbr;
	double		modulo;
	int			neg;

	neg = 0;
	f->i = 0;
	nbr = va_arg(*list, double);
	f->flag[0] = 6;
	f->len = 0;
	if (nbr == INFINITY)
		return (infin(f));
	negative(f, &nbr, &neg);
	modulo = modulo_f(&f->len, nbr);
	f->len += f->flag[0];
	f->final_arg = (char*)malloc(sizeof(char) * f->len + 1);
	if (neg)
		f->final_arg[f->i++] = '-';
	find_int(&f->i, &nbr, modulo, f);
	find_float(&f->i, nbr, f);
	f->final_arg[--f->i] = '\0';
	f->i = -1;
	while (f->final_arg[++f->i] != '\0')
		buf(f->final_arg[f->i], f);
	end(f);
	return (0);
}
