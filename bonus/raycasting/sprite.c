/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:47:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/25 12:26:45 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_sprite(t_object *obj)
{
	int		i;
	int		j;
	int	temp;

	i = -1;
	while (++i < obj->nb_obj)
	{
		j = -1;
		while (++j + 1 < obj->nb_obj)
		{
			if (obj->dist[j + 1] > obj->dist[j])
			{
				ft_swap(&obj->dist[j + 1], &obj->dist[j]);
				temp = obj->order[j + 1];
				obj->order[j + 1] = obj->order[j];
				obj->order[j] = temp;
			}
		}
	}
	
}

t_sprite	*ft_get_cur_sprite(t_game *game)
{
	int	i;
	
	i = -1;
	while (++i < game->object->nb_obj)
	{
		if (game->object->objects[i]->pos->x == game->object->s_x + game->player->pos->x
			&& game->object->objects[i]->pos->y == game->object->s_y + game->player->pos->y)
			return (game->object->objects[i]);
	}
	return (NULL);
}

void	ft_prepare_sprite(t_game *game, t_object *obj, int *i)
{
	t_sprite	*cur;

	obj->s_x = obj->objects[obj->order[*i]]->pos->x - game->player->pos->x;
	obj->s_y = obj->objects[obj->order[*i]]->pos->y - game->player->pos->y;
	obj->inv = 1.0 / (game->plane->x * game->player->dir->y
		- game->player->dir->x * game->plane->y);
	obj->tr_x = obj->inv * (game->player->dir->y * obj->s_x
		- game->player->dir->x * obj->s_y);
	obj->tr_y = obj->inv * (-(game->plane->y) * obj->s_x
		+ game->plane->x * obj->s_y);
	cur = ft_get_cur_sprite(game);
	if (cur)
	{
		obj->move_screen = (int)(cur->v_offset / obj->tr_y);
		obj->screen_x = (int)((screenWidth / 2) * (1 + obj->tr_x / obj->tr_y));
		obj->s_height = abs((int)(screenHeight / (obj->tr_y))) / cur->v_div;
		obj->start_y = -obj->s_height / 2 + screenHeight / 2 + obj->move_screen;
		if (obj->start_y < 0)
			obj->start_y = 0;
		obj->end_y = obj->s_height / 2 + screenHeight / 2 + obj->move_screen;
		if (obj->end_y >= screenHeight)
			obj->end_y = screenHeight - 1;
		obj->s_width = abs((int)(screenHeight / (obj->tr_y))) / cur->h_div;
		obj->start_x = -obj->s_width / 2 + obj->screen_x;
		if (obj->start_x < 0)
			obj->start_x = 0;
		obj->end_x = obj->s_width / 2 + obj->screen_x;
		if (obj->end_x >= screenWidth)
			obj->end_x = screenWidth - 1;
	}
}

void	ft_color_sprite(t_game *game, int x, int y, int i)
{
	t_object	*obj;
	t_sprite	*cur_sprite;

	obj = game->object;
	obj->d = (y - obj->move_screen) * 256 - screenHeight
		* 128 + obj->s_height * 128;
	obj->tex_y = ((obj->d * SPRITE_SIZE) / obj->s_height) / 256;
	cur_sprite = ft_get_cur_sprite(game);
	if (cur_sprite)
	{
		obj->color = ft_get_pixel(cur_sprite->texture, obj->tex_x
			+ SPRITE_SIZE * cur_sprite->frame, obj->tex_y);
		if (obj->color != (0xFF << 24))
		{
			ft_fog(obj->dist[i] / SHADING_DISTANCE, &obj->color);
			ft_put_pixel(game->img, x, y, obj->color);
		}
	}
}

void	ft_draw_sprite(t_game *game, t_object *obj, int i)
{
	int	x;
	int	y;

	x = obj->start_x - 1;
	while (++x < obj->end_x)
	{
		obj->tex_x = (int)(256 * (x - (-obj->s_width / 2 + obj->screen_x))
			* SPRITE_SIZE / obj->s_height) / 256;
		if (obj->tr_y > 0 && x > 0 && x < screenWidth
			&& obj->tr_y < obj->zbuff[x])
		{
			y = obj->start_y - 1;
			while (++y < obj->end_y)
				ft_color_sprite(game, x, y, i);
		}
	}
}
