/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:48:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/18 21:15:09 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	else if (game->map->map[y][x] == 7)
		square.color = 0xDC143C;
	else if (game->map->map[y][x] == 2 || game->map->map[y][x] == 5)
		square.color = 0x1E90FF;
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
