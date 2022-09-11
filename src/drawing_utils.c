/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:25:49 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/05 14:49:53 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_rgbtoi(int r, int g, int b)
{
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF)));
}

void	ft_itorgb(int val, int *r, int *g, int *b)
{
	*r = (val >> 16) & 0xFF;
	*g = (val >> 8) & 0xFF;
	*b = val & 0xFF;
}

void	ft_fog(double dist, int *color)
{
	int		r;
	int		g;
	int		b;
	double	intensity;

	ft_itorgb(*color, &r, &g, &b);
	intensity = (dist) / SHADING_DISTANCE;
	if (intensity > 1)
		intensity = 1;
	r = (1 - intensity) * r + intensity * 0;
	g = (1 - intensity) * g + intensity * 0;
	b = (1 - intensity) * b + intensity * 0;
	*color = ft_rgbtoi(r, g, b);
}
