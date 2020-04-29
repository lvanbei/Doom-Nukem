/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-moff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:22:14 by hde-moff          #+#    #+#             */
/*   Updated: 2020/01/28 10:22:15 by hde-moff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

double	cross_product(double x0, double y0, double x1, double y1)
{
	return ((x0 * y1) - (x1 * y0));
}

int		sign(double x)
{
	if (x < 0)
		return (-1);
	return (1);
}
