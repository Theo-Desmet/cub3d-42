/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:49:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/11 12:16:25 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// void	ft_update_sprite(t_game *game, t_sprite *sprite)
// {
// 	int			type;
// 	static int	replace;

// 	if (((int)sprite->pos->x != (int)sprite->last_pos->x)
// 		|| ((int)sprite->pos->y != (int)sprite->last_pos->y))
// 	{
// 		type = game->map->map[(int)sprite->last_pos->y]
// 		[(int)sprite->last_pos->x];
// 		if (game->map->map[(int)sprite->last_pos->y]
// 			[(int)sprite->last_pos->x] != 0)
// 			replace = game->map->map[(int)sprite->last_pos->y]
// 			[(int)sprite->last_pos->x];
// 		game->map->map[(int)sprite->last_pos->y]
// 		[(int)sprite->last_pos->x] = replace;
// 		sprite->last_pos->y = sprite->pos->y;
// 		sprite->last_pos->x = sprite->pos->x;
// 		game->map->map[(int)sprite->pos->y][(int)sprite->pos->x] = type;
// 	}
// }

void	ft_sprite_cast(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->object->nb_obj)
	{
		game->object->order[i] = i;
		game->object->dist[i] = (pow(game->player->pos->x
					- game->object->objects[i]->pos->x, 2)
				+ pow(game->player->pos->y
					- game->object->objects[i]->pos->y, 2));
	}
	ft_sort_sprite(game->object);
	i = -1;
	while (++i < game->object->nb_obj)
	{
		ft_prepare_sprite(game, game->object, &i);
		if (game->object->end_x < 0)
			game->object->end_x = 0;
		ft_draw_sprite(game, game->object, i);
	}
}

void	ft_draw_gun(t_game *game, int frame)
{
	int			x;
	int			y;
	t_square	square;
	t_vector	pos;

	y = -1;
	pos.x = (S_WIDTH - (SP_SIZE * SIZE_GUN)) / 2;
	pos.y = (S_HEIGHT - SP_SIZE * SIZE_GUN);
	while (++y < SP_SIZE)
	{
		pos.x = (S_WIDTH - (SP_SIZE * SIZE_GUN)) / 2;
		x = -1;
		while (++x < SP_SIZE)
		{		
			square.color = ft_get_pixel(game->assets->gun, x
					+ (SP_SIZE * frame), y);
			if (!(square.color == (0xFF << 24)))
			{
				square = (t_square){pos, SIZE_GUN, square.color, 0, false};
				ft_draw_square(game, square);
			}
			pos.x += SIZE_GUN;
		}
		pos.y += SIZE_GUN;
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

	render = malloc(sizeof(t_render));
	if (!render)
		return ;
	ft_memset((void *)render, 0, sizeof(t_render));
	ft_move(game);
	ft_floor(game, render);
	while (render->x < S_WIDTH)
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
