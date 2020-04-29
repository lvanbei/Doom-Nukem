/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:22:07 by hde-moff          #+#    #+#             */
/*   Updated: 2020/02/25 10:12:19 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int			verify_code(int fd)
{
	char	str[9];

	if (read(fd, str, 8) != 8)
		return (0);
	str[8] = 0;
	if (slow_strcmp(str, "FUCKYOU!") != 0)
		return (0);
	return (1);
}

int			read_player(int fd, t_thing *player)
{
	if (read(fd, player, sizeof(t_thing)) != sizeof(t_thing))
		return (0);
	return (1);
}
