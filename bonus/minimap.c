/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:48:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/04 11:12:20 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_trans(int color, int back)
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

bool	ft_is_in_limit(double x, double y, int radius, int mode)
{
	double	dist;

	if (!mode)
		return (true);
	dist = hypot(x - radius, y - radius);
	if (mode <= 2)
	{
		if (dist > radius)
			return (false);
		if (mode == 2)
			return (dist >= radius - 3);
		return (true);
	}
	else if (mode == 3)
		return (dist < (SIZE_PLAYER / 3));
	return (false);
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
						ft_trans(ft_get_pixel(game->img, x, y), square.color));
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

void	ft_draw_player(t_game *game, int color)
{
	t_vector	v1;
	t_vector	v2;
	t_square	square;
	int			i;

	i = -1;
	v2 = (t_vector){(SIZE_MAP) + LEN_PL * game->player->dir->x,
		((SIZE_MAP) + LEN_PL * game->player->dir->y)};
	while (++i <= SIZE_PLAYER / 4)
	{
		v1 = (t_vector){SIZE_MAP + i, SIZE_MAP};
		ft_draw_line(game, &v1, &v2, color);
		v1 = (t_vector){SIZE_MAP - i, SIZE_MAP};
		ft_draw_line(game, &v1, &v2, color);
		v1 = (t_vector){SIZE_MAP, SIZE_MAP + i};
		ft_draw_line(game, &v1, &v2, color);
		v1 = (t_vector){SIZE_MAP, SIZE_MAP - i};
		ft_draw_line(game, &v1, &v2, color);
	}
	v1 = (t_vector){SIZE_MAP - (SIZE_PLAYER / 2), SIZE_MAP - (SIZE_PLAYER / 2)};
	square = (t_square){v1, SIZE_PLAYER, color, 3, false};
	ft_draw_square(game, square);
}

void	ft_draw_tiles(t_game *game, t_square square, int x, int y)
{
	t_vector	pos;

	pos = (t_vector){(x * SIZE_TILE)
		- (game->player->pos->x * SIZE_TILE) + SIZE_MAP,
		(y * SIZE_TILE) - (game->player->pos->y * SIZE_TILE)
		+ SIZE_MAP};
	square.pos = pos;
	if (game->map->map[y][x] == 1)
		square.color = 0x3B3B3B;
	else if (game->map->map[y][x] == 3)
		square.color = 0xFAD02C;
	else if (game->map->map[y][x] == 4)
		square.color = 0x0A7029;
	if (game->map->map[y][x] != -1)
		ft_draw_square(game, square);
}

void	ft_draw_minimap(t_game *game)
{
	int			x;
	int			y;
	t_vector	pos;
	t_square	square;

	pos = (t_vector){0, 0};
	square = (t_square){pos, (SIZE_TILE + 1) * VIS, 0xFFFFFF, 1, true};
	ft_draw_square(game, square);
	square.size = SIZE_TILE - 1;
	y = fmax(0.0, game->player->pos->y - (VIS / 2)) - 1;
	while (++y <= game->player->pos->y + (VIS / 2) && y < game->map->height)
	{
		x = fmax(0.0, game->player->pos->x - (VIS / 2)) - 1;
		while (++x <= game->player->pos->x + (VIS / 2) && x < game->map->width)
		{
			if (game->map->map[y][x] == 0)
				continue ;
			ft_draw_tiles(game, square, x, y);
		}
	}
	pos = (t_vector){0, 0};
	square = (t_square){pos, (SIZE_TILE + 1) * VIS, 0, 2, false};
	ft_draw_square(game, square);
	ft_draw_player(game, 0xFF);
}
