/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slow_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:40 by hde-moff          #+#    #+#             */
/*   Updated: 2019/11/25 15:52:05 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void				*slow_memcpy(void *restrict dst, const void *restrict src,
size_t n)
{
	char			*d;
	const char		*s;

	d = dst;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

void				*slow_memset(void *dst, int c, size_t n)
{
	unsigned char	*d;

	d = dst;
	while (n--)
		*d++ = c;
	return (dst);
}

void				*slow_bzero(void *dst, size_t n)
{
	unsigned char	*d;

	d = dst;
	while (n--)
		*d++ = 0;
	return (dst);
}

void				*slow_memmove(void *dst, const void *src, size_t n)
{
	char			*d;
	const char		*s;
	char			*reverse_d;
	const char		*reverse_s;

	d = dst;
	s = src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		reverse_d = d + (n - 1);
		reverse_s = s + (n - 1);
		while (n--)
			*reverse_d-- = *reverse_s--;
	}
	return (dst);
}

int					slow_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}
