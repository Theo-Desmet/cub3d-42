/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:25:49 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/24 19:39:24 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

inline int		ft_rgbtoi(int r, int g, int b)
{
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF)));
}

inline void	ft_itorgb(int val, int *r, int *g, int *b)
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

	if (*color == FOG_COLOR)
		return ;
	intensity = (dist) / SHADING_DISTANCE;
	if (intensity > 1)
		intensity = 1;
	else if (intensity < 0)
		intensity = 0;
	if (intensity == 1)
	{
		*color = FOG_COLOR;
		return ;
	}
	ft_itorgb(*color, &r, &g, &b);
	r = (1 - intensity) * r + intensity * (double)((FOG_COLOR >> 16) & 0xFF);
	g = (1 - intensity) * g + intensity * (double)((FOG_COLOR >> 8) & 0xFF);
	b = (1 - intensity) * b + intensity * (double)(FOG_COLOR & 0xFF);
	*color = ft_rgbtoi(r, g, b);
}
