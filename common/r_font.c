/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_font.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:22:07 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 10:12:19 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int					read_font_table(char font_table[128][8])
{
	int				fd;

	fd = open("res/font.dat", O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, font_table, 128 * 8) != 128 * 8)
		return (0);
	return (1);
}

static inline void	char_to_screen(SDL_Surface *screen, t_text *t, char c)
{
	unsigned char	i;
	unsigned char	j;
	const char		*font;

	font = (*t->font_table)[(int)c];
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (font[j] & 1 << i)
				((uint32_t *)screen->pixels)[(t->x + i) +
					screen->w * (t->y + j)] = t->color;
			j++;
		}
		i++;
	}
}

int					print_to_screen(SDL_Surface *screen, t_text t,
		char *format, ...)
{
	char			buffer[256];
	int				i;
	int				ret;
	va_list			args;

	va_start(args, format);
	ret = ft_vsprintf(buffer, format, args);
	i = 0;
	while (buffer[i])
	{
		char_to_screen(screen, &t, buffer[i++]);
		t.x += 8;
	}
	va_end(args);
	return (ret);
}
