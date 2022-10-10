/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:41:49 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/08 12:53:00 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

inline int	ft_clamp(int x, int low, int high)
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

	x = ft_clamp(x, 0, img->width);
	y = ft_clamp(y, 0, img->height);
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

void	ft_draw_square(t_game *game, t_square square)
{
	double	x;
	double	y;

	y = square.pos.y;
	while (y++ < square.pos.y + square.size)
	{
		x = square.pos.x;
		while (x++ < square.pos.x + square.size)
		{
			if (ft_is_in_limit(x, y, SIZE_MAP, square.mode))
			{
				if (square.is_transparent)
					ft_put_pixel(game->img, x, y,
						ft_transp(ft_get_pixel(game->img, x, y), square.color));
				else
					ft_put_pixel(game->img, x, y, square.color);
			}
		}
	}
}

void	ft_draw_line(t_game *game, t_vector *pos, t_vector *pos2, int color)
{
	double		dx;
	double		dy;
	int			pixels;
	t_vector	coord;

	dx = pos2->x - pos->x;
	dy = pos2->y - pos->y;
	pixels = hypot(dx, dy);
	dx /= pixels;
	dy /= pixels;
	coord = (t_vector){pos->x, pos->y};
	while (pixels)
	{
		ft_put_pixel(game->img, coord.x, coord.y, color);
		coord = (t_vector){coord.x += dx, coord.y += dy};
		pixels--;
	}
}
