/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:39:27 by lvan-bei          #+#    #+#             */
/*   Updated: 2020/02/13 18:45:13 by lvan-bei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

uintmax_t		ft_sign(intmax_t nbr, t_flag *f)
{
	f->sign = '+';
	if (nbr < 0)
	{
		f->sign = '-';
		nbr *= -1;
	}
	return (nbr);
}

char			*ft_itoa_base(uintmax_t nbr, int base, t_flag *f)
{
	static char	convert[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
		'9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int			converted_nbr[64];
	char		*result;
	uintmax_t	n;
	intmax_t	i;

	i = 0;
	n = (intmax_t)nbr;
	if (nbr == 0)
		return ("0");
	while (n > 0)
	{
		converted_nbr[i++] = n % base;
		n /= base;
	}
	result = (char*)malloc(sizeof(char) * --i);
	result[i + 1] = '\0';
	while (i >= 0 && f->flag_char == 'x')
		result[n++] = ft_tolower(convert[converted_nbr[i--]]);
	while (i >= 0)
		result[n++] = convert[converted_nbr[i--]];
	return (result);
}

char			*ft_tolower_str(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		str[i] = ft_tolower(str[i]);
	}
	return (str);
}

void			negative(t_flag *f, double *nbr, int *neg)
{
	if (*nbr < 0)
	{
		f->len++;
		*nbr *= -1;
		*neg = 1;
	}
}

void			apply_mask(t_flag *f, int *mask)
{
	int i;

	i = 2;
	while (++i < 14)
		f->flag[i] = f->flag[i] * mask[i];
}
