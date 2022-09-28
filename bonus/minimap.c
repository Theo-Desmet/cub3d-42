/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:48:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/28 23:22:06 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_trans(int color, int back)
{
	t_rgb	colorRGB;
	t_rgb	backRGB;
	double	opacity;
	ft_itorgb(color, &colorRGB.r, &colorRGB.g, &colorRGB.b);
	ft_itorgb(back, &backRGB.r, &backRGB.g, &backRGB.b);
	opacity = 0.5;
	colorRGB.r = (int)(((double)backRGB.r * opacity) + ((double)colorRGB.r * (1.0 - opacity)));
	colorRGB.g = (int)(((double)backRGB.g * opacity) + ((double)colorRGB.g * (1.0 - opacity)));
	colorRGB.b = (int)(((double)backRGB.b * opacity) + ((double)colorRGB.b * (1.0 - opacity)));
	return (ft_rgbtoi(colorRGB.r, colorRGB.g, colorRGB.b));
}

enum MAP {
	SIZE_MAP = 80,
	VISIBILITY = 15,
	SIZE_TILE = (SIZE_MAP * 2) / VISIBILITY,
	SIZE_PLAYER = 15,
	LEN_PL = (SIZE_PLAYER)
};

bool	ft_is_in_limit(double x, double y, int center_circle)
{
	double	dist;

	dist = hypot(x - center_circle, y - center_circle);
	if (dist <= center_circle)
		return (true);
	return (false);
}

void	ft_draw_squa(t_game *game, t_vector pos, int color, int size)
{
	double	x;
	double	y;

	y = pos.y;
	while (y++ < pos.y + size)
	{
		x = pos.x;
		while (x++ < pos.x + size)
			if (ft_is_in_limit(x, y, (SIZE_MAP)))
				ft_put_pixel(game->img, x, y, color);
	}
}

bool	ft_is_in_limit2(double x, double y, int center_circle)
{
	double	dist;

	dist = hypot(x - center_circle, y - center_circle);
	if (dist <= center_circle && dist >= center_circle - 3)
		return (true);
	return (false);
}

void	ft_draw_squa2(t_game *game, t_vector pos, int color, int size)
{
	double	x;
	double	y;

	y = pos.y;
	while (y++ < pos.y + size)
	{
		x = pos.x;
		while (x++ < pos.x + size)
			if (ft_is_in_limit2(x, y, (SIZE_MAP)))
				ft_put_pixel(game->img, (int)x, (int)y, color);
	}
}

void	ft_draw_trans_squa(t_game *game, t_vector pos, int color, int size)
{
	double	x;
	double	y;

	y = pos.y;
	while (y++ < pos.y + size)
	{
		x = pos.x;
		while (x++ < pos.x + size)
			if (ft_is_in_limit(x, y, (SIZE_MAP)))
				ft_put_pixel(game->img, x, y, ft_trans(ft_get_pixel(game->img, x, y), color));
	}
}

static void	ft_draw_square3(t_game *game, t_vector pos, int color, int size)
{
	double	x;
	double	y;

	y = pos.y;
	while (y++ < pos.y + size)
	{
		x = pos.x;
		while (x++ < pos.x + size)
			ft_put_pixel(game->img, x, y, color);
	}
}

void	ft_draw_line(t_game *game, t_vector *pos, t_vector *pos2, int color)
{
	double		dx;
	double		dy;
	int			pixels;
	t_vector	coord;
	t_vector	temp;

	dx = pos2->x - pos->x;
	dy = pos2->y - pos->y;
	pixels = hypot(dx, dy);
	dx /= pixels;
	dy /= pixels;
	coord = (t_vector){pos->x, pos->y};
	temp = (t_vector){coord.x, coord.y};
	while (pixels)
	{
		temp.x += dx;
		temp.y += dy;
		ft_put_pixel(game->img, coord.x, coord.y, color);
		coord = (t_vector){temp.x, temp.y};
		pixels--;
	}
}

bool	ft_is_in_limit4(double x, double y, int center_circle)
{
	double	dist;

	dist = hypot(x - center_circle, y - center_circle);
	if (dist < (SIZE_PLAYER / 3))
		return (true);
	return (false);
}

void	ft_draw_squa4(t_game *game, t_vector pos, int color, int size)
{
	double	x;
	double	y;

	y = pos.y;
	while (y++ < pos.y + size)
	{
		x = pos.x;
		while (x++ < pos.x + size)
			if (ft_is_in_limit4(x, y, (SIZE_MAP)))
				ft_put_pixel(game->img, (int)x, (int)y, color);
	}
}

void	ft_draw_player(t_game *game, int color)
{

	t_vector	v1;
	t_vector	v2;
	int			i;

	i = -1;
	v2 = (t_vector){(SIZE_MAP) + LEN_PL * game->player->dir->x, ((SIZE_MAP) + LEN_PL * game->player->dir->y)};
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
	ft_draw_squa4(game, v1, 0xFF, SIZE_PLAYER);
}

void	ft_draw_minimap(t_game *game)
{
	int	x;
	int	y;
	t_vector	pos;


	pos.x = 0;
	pos.y = 0;
	ft_draw_trans_squa(game, pos, 0xFFFFFF, (SIZE_TILE + 1) * VISIBILITY);
	y = fmax(0.0, game->player->pos->y - (VISIBILITY / 2));
	while (y <= game->player->pos->y + (VISIBILITY / 2) && y < game->map->height)
	{
		x = fmax(0.0, game->player->pos->x - (VISIBILITY / 2));
		while (x <= game->player->pos->x + (VISIBILITY / 2) && x < game->map->width)
		{
			pos.y = (y * SIZE_TILE) - (game->player->pos->y * SIZE_TILE) + SIZE_MAP;
			pos.x = (x * SIZE_TILE) - (game->player->pos->x * SIZE_TILE) + SIZE_MAP;
			if (game->map->map[y][x] == 1)
				ft_draw_trans_squa(game, pos, 0x3B3B3B, SIZE_TILE - 1);
			if (game->map->map[y][x] == 3)
				ft_draw_trans_squa(game, pos, 0xFAD02C, SIZE_TILE - 1);
			if (game->map->map[y][x] == 4)
				ft_draw_trans_squa(game, pos, 0x0A7029, SIZE_TILE - 1);				
			x++;
		}
		y++;
	}
	pos.x = 0;
	pos.y = 0;
	ft_draw_squa2(game, pos, 0, (SIZE_TILE + 1) * VISIBILITY); // OUTLINE
	ft_draw_player(game, 0xFF);
	// pos.x = (SIZE_MAP) - 3;
	// pos.y = (SIZE_MAP) - 3;
	// ft_draw_squa(game, pos, 0xFF0000, 6); // PLAYER




}