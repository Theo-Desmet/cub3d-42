/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:34 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/07 12:24:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_key_down(int keycode, t_game *game)
{
	if (keycode == 65507)
		game->shooting = true;
	if (keycode == 65505)
		game->player->walk_speed = 0.16;
	if (keycode == 65513)
		game->player->walk_speed = 0.04;
	if (keycode == FORWARD_KEY)
		game->forward = true;
	if (keycode == BACKWARD_KEY)
		game->backward = true;
	if (keycode == STRAFE_LEFT_KEY)
		game->left = true;
	if (keycode == STRAFE_RIGHT_KEY)
		game->right = true;
	if (keycode == 65363)
		game->r_right = true;
	if (keycode == 65361)
		game->r_left = true;
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	return (0);
}

void	ft_door(t_game *game)
{
	t_door	*door;

	door = ft_get_cur_door(game, (int)(game->player->pos->x
				+ game->player->dir->x), (int)(game->player->pos->y
				+ game->player->dir->y));
	if (door)
		door->state *= -1;
}

int	ft_key_up(int keycode, t_game *game)
{
	if (keycode == 65505 || keycode == 65513)
		game->player->walk_speed = MOVING_SPEED;
	if (keycode == FORWARD_KEY)
		game->forward = false;
	if (keycode == ' ')
		ft_door(game);
	if (keycode == BACKWARD_KEY)
		game->backward = false;
	if (keycode == STRAFE_LEFT_KEY)
		game->left = false;
	if (keycode == STRAFE_RIGHT_KEY)
		game->right = false;
	if (keycode == 65363)
		game->r_right = false;
	if (keycode == 65361)
		game->r_left = false;
	return (0);
}

void	ft_animation_handler(t_object *obj, int i)
{
	if (obj->objects[i]->animated)
	{
		if (obj->tick == 25)
			obj->objects[i]->frame = 1;
		if (obj->tick == 50)
			obj->objects[i]->frame = 2;
		if (obj->tick == 75)
			obj->objects[i]->frame = 3;
		if (obj->tick == 120)
		{
			obj->objects[i]->frame = 0;
			obj->tick = 0;
		}
	}	
}

int	ft_loop(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->nb_doors)
	{
		game->doors[i]->factor -= DOOR_SPEED * game->doors[i]->state;
		if (game->doors[i]->factor > 1.0)
			game->doors[i]->factor = 1;
		if (game->doors[i]->factor < 0.0)
			game->doors[i]->factor = 0.0;
	}
	i = -1;
	game->object->tick++;
	while (++i < game->object->nb_obj)
		ft_animation_handler(game->object, i);
	ft_pathfinding(game, game->enemy, game->map);
	game->enemy->sprite->pos->x = game->enemy->act->x;
	game->enemy->sprite->pos->y = game->enemy->act->y;
	ft_render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->mlx_img, 0, 0);
	ft_fps(game);
	return (0);
}
