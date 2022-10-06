/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:25:49 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/06 15:05:33 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

double	ft_clampf(double x, double low, double high)
{
	if (x > high)
		x = high;
	if (x < low)
		x = low;
	return (x);
}

void	ft_fog(double dist, int *color)
{
	t_rgb	rgb;
	double	intensity;

	if (*color == FOG_COLOR)
		return ;
	intensity = (dist) / SHADING_DISTANCE;
	intensity = ft_clampf(intensity, 0, 1);
	if (intensity == 1)
	{
		*color = FOG_COLOR;
		return ;
	}
	ft_itorgb(*color, &rgb.r, &rgb.g, &rgb.b);
	rgb.r = (1 - intensity) * rgb.r + intensity
		* (double)((FOG_COLOR >> 16) & 0xFF);
	rgb.g = (1 - intensity) * rgb.g + intensity
		* (double)((FOG_COLOR >> 8) & 0xFF);
	rgb.b = (1 - intensity) * rgb.b + intensity * (double)(FOG_COLOR & 0xFF);
	*color = ft_rgbtoi(rgb.r, rgb.g, rgb.b);
}

int	ft_transp(int color, int back)
{
	t_rgb	color_rgb;
	t_rgb	back_rgb;
	double	opacity;

	ft_itorgb(color, &color_rgb.r, &color_rgb.g, &color_rgb.b);
	ft_itorgb(back, &back_rgb.r, &back_rgb.g, &back_rgb.b);
	opacity = 0.5;
	color_rgb.r = (int)(((double)back_rgb.r * opacity)
			+ ((double)color_rgb.r * (1.0 - opacity)));
	color_rgb.g = (int)(((double)back_rgb.g * opacity)
			+ ((double)color_rgb.g * (1.0 - opacity)));
	color_rgb.b = (int)(((double)back_rgb.b * opacity)
			+ ((double)color_rgb.b * (1.0 - opacity)));
	return (ft_rgbtoi(color_rgb.r, color_rgb.g, color_rgb.b));
}
