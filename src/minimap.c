/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:48:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/09 16:19:21 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	*ft_vector_dup(t_vector *vector)
{
	t_vector	*dup;

	dup = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	dup->x = vector->x;
	dup->y = vector->y;
	return (dup);
}

void	ft_draw_line(t_img *img, t_vector *pos, t_vector *pos2)
{
	double		dx;
	double		dy;
	int			pixels;
	t_vector	*coord;
	t_vector	*temp;

	dx = pos2->x - pos->x;
	dy = pos2->y - pos->y;
	pixels = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
	dx /= pixels;
	dy /= pixels;
	coord = ft_init_vector(pos->x, pos->y);
	temp = ft_vector_dup(coord);
	while (pixels)
	{
		temp->x += dx;
		temp->y += dy;
		ft_draw_square(img, coord, 1, 0x00FF00);
		coord = ft_vector_dup(temp);
		pixels--;
	}
	free(pos);
	free(pos2);
	free(temp);
	free(coord);
}

void	ft_draw_player_minimap(t_game *game)
{
	int			size;
	t_player	*p;

	size = 10;
	p = game->player;
	// ft_draw_circle(game->img, ft_init_vector((mapWidth * size - game->player->pos->x * size), (game->player->pos->y * size)), 4, 0xFF0000);
	ft_draw_line(game->img, ft_init_vector((mapWidth * size - p->pos->x
				* size) - 1, (p->pos->y * size) - 1),
		ft_init_vector((mapWidth * size - p->pos->x * size - p->dir->x
				* p->walk_speed * 200),
			(p->pos->y * size + p->dir->y * p->walk_speed * 200)));
	ft_draw_square(game->img, ft_init_vector((int)(mapWidth * size - p->pos->x
				* size) - 3, (int)(p->pos->y * size) - 3), 6, 0xFF0000);
	// ft_draw_line(game->img, ft_init_vector(0, 0), ft_init_vector(100, 100));
}

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

void	ft_color_minimap(t_game *game, int *data)
{
	if (worldMap[data[3]][data[0]] == 1)
		ft_draw_trans(game, ft_init_vector(mapWidth * 10 - data[2] - 10,
				data[1]), 10, 0x60);
	else if (worldMap[data[3]][data[0]] == 2 || worldMap[data[3]][data[0]] == 3)
		ft_draw_square(game->img, ft_init_vector(mapWidth * 10 - data[2] - 10,
				data[1]), 10, 0xFFD700);
	else
		ft_draw_trans(game, ft_init_vector(mapWidth * 10 - data[2] - 10,
				data[1]), 10, 0x0000FF);
	data[2] += 10;
}

void	ft_draw_minimap(t_game *game)
{
	int	data[4];

	data[0] = -1;
	data[1] = 0;
	while (++data[0] < mapHeight)
	{
		data[3] = -1;
		data[2] = 0;
		while (++data[3] < mapWidth)
			ft_color_minimap(game, data);
		data[1] += 10;
		ft_draw_player_minimap(game);
	}
}
