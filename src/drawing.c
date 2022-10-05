/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:41:49 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/04 11:34:49 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height
		|| (int)ft_get_pixel(img, x, y) == color)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_clamp(int x, int low, int high)
{
	if (x > high)
		x = high;
	if (x < low)
		x = low;
	return (x);
}

unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	static int			cache_x;
	static int			cache_y;
	static t_img		*cache_img;
	static unsigned int	cache_color;

	x = ft_clamp(x, 0, S_WIDTH);
	y = ft_clamp(y, 0, S_HEIGHT);
	if (x != cache_x || y != cache_y || img != cache_img)
	{
		cache_color = *(unsigned int *)(img->addr
				+ (y * img->line_len + x * (img->bpp / 8)));
		cache_x = x;
		cache_y = y;
		cache_img = img;
	}
	return (cache_color);
}
