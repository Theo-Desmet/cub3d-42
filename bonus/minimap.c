/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:48:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/25 10:36:05 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

	// ft_draw_line(game->img, ft_init_vector((mapWidth * size - p->pos->x
	// 			* size) - 1, (p->pos->y * size) - 1),
	// 	ft_init_vector((mapWidth * size - p->pos->x * size - p->dir->x * p->walk_speed * 200),
	// 		(p->pos->y * size + p->dir->y * p->walk_speed * 200)));

	// ft_draw_square(game->img, ft_init_vector((int)(mapWidth * size - p->pos->x
	// 			* size) - 3, (int)(p->pos->y * size) - 3), 6, 0xFF0000);
	int offset = 3;
	ft_draw_line(game->img, ft_init_vector(p->pos->y * size + offset, p->pos->x * size + offset),
		ft_init_vector(p->pos->y * size + p->dir->y * p->walk_speed * 200 + offset, p->pos->x * size + p->dir->x * p->walk_speed * 200 + offset));
	ft_draw_square(game->img, ft_init_vector(p->pos->y * size, p->pos->x * size), 6, 0xFF);

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

// void	ft_draw_minimap(t_game *game)
// {
// 	int x;
// 	int	y;
	
// 	y = -1;
// 	while (++y < mapHeight)
// 	{
// 		x = -1;
// 		while (++x < mapWidth)
// 		{
// 			if (worldMap[y][x] == 1)
// 				ft_draw_trans(game, ft_init_vector(x * 10, y * 10), 10, 0x60);
// 			else
// 				ft_draw_trans(game, ft_init_vector(10 * x, y * 10), 10, 0x0000FF);
// 		}
// 	}
// 	ft_draw_player_minimap(game);
// }

#define ZOOM 10
#define FACT 10
#define OFFSET 10
#define NUMBER 21
#define SIZE 15



// void	ft_draw_minimap(t_game *game)
// {
// 	ft_draw_trans(game, ft_init_vector(OFFSET, OFFSET), SIZE * NUMBER, 0x0000FF);
// 	int	x;
// 	int	y;
// 	int	end_x;
// 	int	end_y;
// 	int	start_x;
// 	int	start_y;

// 	x = game->player->pos->x - ZOOM;
// 	y = game->player->pos->y - ZOOM;

// 	start_x	= x;
// 	start_y = y;

// 	end_y = game->player->pos->y + ZOOM;
// 	if (end_y > game->map->height - 1)
// 		end_y = game->map->height - 1;
// 	end_x = game->player->pos->x + ZOOM;
// 		if (end_x > game->map->width - 1)
// 			end_x = game->map->width - 1;
// 	int a = end_x - start_x;
// 	int b = end_y - start_y;
// 	while (y <= end_y)
// 	{
// 		x = game->player->pos->x - ZOOM;
// 		if (x < 0)
// 			x = 0;
// 		while (x <= end_x)
// 		{
// 			if (worldMap[y][x] == 1)
// 			{
				
// 				ft_draw_trans(game, ft_init_vector(((x - start_x) * FACT + 10), ((y - start_y) * FACT + 10)), FACT, 0x60);
// 			}
// 			else
// 				ft_draw_trans(game, ft_init_vector((x - start_x) * FACT + 10, (y - start_y) * FACT + 10), FACT, 0x0000FF);
// 			x++;
// 		}
// 		y++;
// 	}
// 	// ft_draw_trans(game, ft_init_vector(OFFSET, OFFSET), SIZE * NUMBER, 0x0000FF);
// 	ft_draw_square(game->img, ft_init_vector((SIZE * NUMBER) / 2 + OFFSET, (SIZE * NUMBER) / 2 + OFFSET), 8, 0xFF);

// 	// ft_draw_square(game->img, ft_init_vector((a / 2) * FACT, (b / 2) * FACT), 15, 0xFF);
// }


// void	ft_color_minimap(t_game *game, int *data)
// {
// 	if (worldMap[data[0]][data[3]] == 1)
// 		ft_draw_trans(game, ft_init_vector(mapWidth * 10 - data[2] - 10,
// 				data[1]), 10, 0x60);
// 	else if (worldMap[data[0]][data[3]] == 2 || worldMap[data[0]][data[3]] == 3 || worldMap[data[0]][data[3]] == 4)
// 		ft_draw_square(game->img, ft_init_vector(mapWidth * 10 - data[2] - 10,
// 				data[1]), 10, 0xFFD700);
// 	else
// 		ft_draw_trans(game, ft_init_vector(mapWidth * 10 - data[2] - 10,
// 				data[1]), 10, 0x0000FF);
// 	data[2] += 10;
// }

// void	ft_draw_minimap(t_game *game)
// {
// 	int	data[4];

// 	data[0] = -1;
// 	data[1] = 0;
// 	while (++data[0] < mapHeight)
// 	{
// 		data[3] = -1;
// 		data[2] = 0;
// 		while (++data[3] < mapWidth)
// 			ft_color_minimap(game, data);
// 		data[1] += 10;
// 	}
// }


// void	ft_draw_minimap(t_game *game)
// {
// 	// ft_draw_trans(game, ft_init_vector(OFFSET, OFFSET), SIZE * NUMBER, 0x0000FF);
// 	int	startMapX;
// 	int	startMapY;
// 	int	endMapX;
// 	int	endMapY;
// 	int	screenX;
// 	int	screenY;

// 	startMapX = game->player->pos->x - ZOOM;
// 	startMapY = game->player->pos->y - ZOOM;
// 	endMapX = game->player->pos->x + ZOOM;
// 	if (endMapX > game->map->width - 1)
// 		endMapX = game->map->width - 1;
// 	endMapY = game->player->pos->y + ZOOM;
// 	if (endMapY > game->map->height - 1)
// 		endMapY = game->map->height - 1;
	
// 	int	y = startMapY;
// 	while (y <= endMapY)
// 	{
// 		int	x = startMapX;
// 		while (x <= endMapX)
// 		{
// 			if (x < 0)
// 			{
// 				x++;
// 				continue;
// 			}
// 			if (y < 0)
// 			{
// 				y++;
// 				continue;
// 			}
// 			// if (worldMap[y][x] != 0)
// 			// 	ft_draw_trans(game, ft_init_vector(((y - startMapY) * FACT + OFFSET), ((endMapX - x - startMapX)  * FACT + OFFSET)), FACT, 0x60);
// 			// else
// 			// 	ft_draw_trans(game, ft_init_vector(((y - startMapY) * FACT + OFFSET), ((endMapX - x - startMapX)  * FACT + OFFSET)), FACT, 0x0000FF);
// 			if (worldMap[y][x] != 0)
// 				ft_draw_trans(game, ft_init_vector(((y - startMapY)  * SIZE + OFFSET), ((x - startMapX)   * SIZE + OFFSET)), SIZE, 0x60);
// 			else
// 				ft_draw_trans(game, ft_init_vector(((y - startMapY)  * SIZE + OFFSET), ((x - startMapX)   * SIZE + OFFSET)), SIZE, 0x0000FF);
// 			x++;
// 		}
// 		y++;
// 	}
// 	int origin = OFFSET + (SIZE * NUMBER) / 2;
// 	ft_draw_line(game->img, ft_init_vector(origin, origin),
// 						ft_init_vector(origin + game->player->dir->y * 15,
// 							origin + game->player->dir->x * 15));
// 	// printf("%f - %f\n", game->player->pos->x, game->player->pos->y);
// 	// ft_draw_line(game->img, ft_init_vector(p->pos->y * size + offset, p->pos->x * size + offset),
// 	// 	ft_init_vector(p->pos->y * size + p->dir->y * p->walk_speed * 200 + offset, p->pos->x * size + p->dir->x * p->walk_speed * 200 + offset));
	
// }

double cacheX = 11;
double cacheY = 3;

int zoom = 8;

void	ft_draw_minimap(t_game *game)
{
	double	rectX;
	double	rectY;
	int		mapX;
	int		mapY;

	rectX = -(fmod(game->player->pos->x, 1.0)) * SIZE;
	mapX = -zoom;
	while (++mapX < zoom)
	{
		mapY = -zoom;
		rectY = -(fmod(game->player->pos->y, 1.0)) * SIZE;
		while (mapY < zoom)
		{
			int a = mapX + (int)game->player->pos->x;
			int b = mapY + (int)game->player->pos->y;
			if (a >= 0 && b >= 0 && a < game->map->height && b < game->map->width)
			{
				if (game->map->map[a][b] == 1)
					ft_draw_trans(game, ft_init_vector(rectY, rectX), SIZE, 0x60);
				else
					ft_draw_trans(game, ft_init_vector(rectY, rectX), SIZE, 0x0000FF);
			}
			rectY += SIZE;
			mapY++;
		}
		rectX += SIZE;
	}
	// ft_draw_square(game->img, ft_init_vector(game->player->pos->y, game->player->pos->x * SIZE), 6, 0xFF);

	// ft_draw_square(game->img, ft_init_vector(rectX - game->player->pos->x * SIZE, rectY - game->player->pos->y * SIZE), 6, 0xFF);
	ft_draw_trans(game, ft_init_vector((rectY - (SIZE)) / 2.0, (rectX - (SIZE)) / 2.0), 8, 0);
}

void	ft_draw_minimap2(t_game *game)
{
	int x;
	int	y;
	
	y = -1;
	while (++y < mapHeight)
	{
		x = -1;
		while (++x < mapWidth)
		{
			if (game->map->map[y][x] == 1)
				ft_draw_trans(game, ft_init_vector(x * 10, y * 10), 10, 0x60);
			else
				ft_draw_trans(game, ft_init_vector(10 * x, y * 10), 10, 0x0000FF);
		}
	}
	ft_draw_player_minimap(game);
	ft_draw_minimap2(game);
}