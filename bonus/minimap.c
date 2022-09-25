/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:48:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/24 19:55:25 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_trans(int color, int back)
{
	int		r;
	int		g;
	int		b;
	double	opacity;

	ft_itorgb(color, &r, &g, &b);
	opacity = 0.3;
	if (back == 0xFFD700)
		return (back);
	r = (int)(opacity * (double)r + (1.0 - opacity) * back);
	g = (int)(opacity * (double)g + (1.0 - opacity) * back);
	b = (int)(opacity * (double)b + (1.0 - opacity) * back);
	return (ft_rgbtoi(r, g, b));
}

void	ft_draw_trans(t_game *game, t_vector *vector, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_put_pixel(game->img, (int)vector->x + i, (int)vector->y + j,
				ft_trans(ft_get_pixel(game->img, (int)vector->x + i,
						(int)vector->y + j), color));
			j++;
		}
		i++;
	}
	free(vector);
}

enum MAP {
	OFFSET = 10,
	SIZE_MAP = 80,
	VISIBILITY = 20,
	SIZE_TILE = (SIZE_MAP * 2) / VISIBILITY,
	SIZE_PLAYER
};

// bool	ft_is_in_limit(double x, double y, int center_circle)
// {
// 	double	dist;

// 	dist = hypot(x - center_circle, y - center_circle);
// 	if (dist <= center_circle - 2)
// 		return (true);
// 	return (false);
// }

bool	ft_is_in_limit(double x, double y)
{
	return ((x <= ((SIZE_TILE) * VISIBILITY) && y <= (SIZE_TILE * VISIBILITY)) && x >= OFFSET && y >= OFFSET);
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
			if (ft_is_in_limit(x, y))
				ft_put_pixel(game->img, (int)x, (int)y, color);
	}
}

void	ft_draw_minimap(t_game *game)
{
	int	x;
	int	y;
	t_vector	pos;


	pos.x = 0;
	pos.y = 0;
	ft_draw_squa(game, pos, 0xFFFFFF, (SIZE_TILE + 1) * VISIBILITY);
	y = fmax(0.0, game->player->pos->y - (VISIBILITY / 2));
	while (y <= game->player->pos->y + (VISIBILITY / 2) && y < game->map->height)
	{
		x = fmax(0.0, game->player->pos->x - (VISIBILITY / 2));
		while (x <= game->player->pos->x + (VISIBILITY / 2) && x < game->map->width)
		{
			pos.y = (y * SIZE_TILE) - (game->player->pos->y * SIZE_TILE) + OFFSET + SIZE_MAP;
			pos.x = (x * SIZE_TILE) - (game->player->pos->x * SIZE_TILE) + OFFSET + SIZE_MAP;
			if (game->map->map[y][x] == 1)
				ft_draw_squa(game, pos, 0xFF, SIZE_TILE - 1);
			x++;
		}
		y++;
	}
	pos.x = OFFSET + SIZE_MAP - 1;
	pos.y = OFFSET + SIZE_MAP - 1;
	ft_draw_squa(game, pos, 0xFF0000, 4);
}