/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:49:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/24 19:54:38 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdbool.h>

t_render	*ft_init_render(void)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	render->end = 0;
	render->start = 0;
	render->x = 0;
	render->y = 0;
	render->color = 0;
	render->sprite_x = 0;
	render->sprite_y = 0;
	render->wall_x = 0;
	return (render);
}

void	ft_update_sprite(t_game *game, t_sprite *sprite)
{
	int	type;

	if (((int)sprite->pos->x != (int)sprite->last_pos->x) ||
		((int)sprite->pos->y != (int)sprite->last_pos->y))
	{
		type = game->map->map[(int)sprite->last_pos->y][(int)sprite->last_pos->x];
		game->map->map[(int)sprite->last_pos->y][(int)sprite->last_pos->x] = 0;
		sprite->last_pos->y = sprite->pos->y;
		sprite->last_pos->x = sprite->pos->x;
		game->map->map[(int)sprite->pos->y][(int)sprite->pos->x] = type;
	}
}

void	ft_sprite_cast(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->object->nb_obj)
	{
		game->object->order[i] = i;
		game->object->dist[i] = (pow(game->player->pos->x
					- game->object->objects[i]->pos->x, 2)
				+ pow(game->player->pos->y - game->object->objects[i]->pos->y, 2));
	}
	ft_sort_sprite(game->object);
	i = -1;
	game->object->h_div = 1;
	game->object->v_div = 1;
	game->object->v_offset = 0;
	while (++i < game->object->nb_obj)
	{
		ft_prepare_sprite(game, game->object, &i);
		if (game->object->end_x < 0)
			game->object->end_x = 0;
		ft_draw_sprite(game, game->object, i);
		ft_update_sprite(game, game->object->objects[i]);
	}
}

void	ft_draw_gun(t_game *game, int frame)
{
	int size = (screenWidth / screenHeight) * (screenHeight / SPRITE_SIZE) / 3;
	int				x1;
	int				y1;
	unsigned int	color;
	int				save;
	t_vector		pos;
	y1 = 0;
	pos = (t_vector){(screenWidth - (SPRITE_SIZE * size)) / 2, (screenHeight - SPRITE_SIZE * size)};
	save = (int)pos.x;
	while (y1 < SPRITE_SIZE)
	{
		pos.x = save;
		x1 = 0;
		while (x1 < SPRITE_SIZE)
		{
			color = ft_get_pixel(game->assets->gun, x1 + (SPRITE_SIZE * frame), y1);
			if (!(color == (unsigned int)(0xFF << 24)))
				ft_draw_square2(game->img, &pos, size, color);
			pos.x += size;
			x1++;
		}
		pos.y += size;
		y1++;
	}
}

void	ft_gun(t_game *game)
{
	if (game->shooting)
	{
		game->frame -= 2;
		if (game->frame >= 50)
			ft_draw_gun(game, 0);
		else if (game->frame >= 40)
			ft_draw_gun(game, 1);
		else if (game->frame >= 30)
			ft_draw_gun(game, 2);
		else if (game->frame >= 20)
			ft_draw_gun(game, 3);
		else if (game->frame >= 10)
			ft_draw_gun(game, 4);
		else
		{
			game->frame = 50;
			game->shooting = false;
			ft_draw_gun(game, 0);
		}
	}
	else
		ft_draw_gun(game, 0);
}

void	ft_render(t_game *game)
{
	t_render	*render;

	render = ft_init_render();
	if (!render)
		return ;
	ft_move(game);

	ft_floor(game, render);

	while (render->x < screenWidth)
	{
		render->x_offset = 0;
		render->y_offset = 0;
		ft_prepare_ray(game, render->x);
		ft_dda(game->ray);
		ft_wall_hit(game->ray, render, game);
		ft_wall_proj(game->ray, render, game);

		game->object->zbuff[render->x] = render->perp_wall_dist;
		render->x++;
	}
	ft_sprite_cast(game);
	ft_gun(game);
	ft_draw_minimap(game);

	free(render);
}
