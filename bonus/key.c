/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:34 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/22 16:28:15 by bbordere         ###   ########.fr       */
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
	if (keycode == 'k')
		game->object->objects[0]->pos->x += 0.1;
	if (keycode == ',')
		game->object->objects[0]->pos->x -= 0.1;
	if (keycode == FORWARD_KEY)
		game->forward = true;
	if (keycode == BACKWARD_KEY)
		game->backward = true;
	if (keycode == STRAFE_LEFT_KEY)
		game->left = true;
	if (keycode == STRAFE_RIGHT_KEY)
		game->right = true;
	if (keycode == 65363)
		game->rotate_right = true;
	if (keycode == 65361)
		game->rotate_left = true;
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	return (0);
}

void	ft_door(t_game *game)
{
	t_door	*door;

	door = ft_get_cur_door(game,(int)(game->player->pos->x + game->player->dir->x),
				(int)(game->player->pos->y + game->player->dir->y));
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
		game->rotate_right = false;
	if (keycode == 65361)
		game->rotate_left = false;
	return (0);
}


void	ft_fps(t_game *game);
int	ft_loop(t_game *game)
{
	int i;

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
	{
		if (game->object->objects[i]->animated)
		{
			if (game->object->tick == 25)
				game->object->objects[i]->frame = 1;
			if (game->object->tick == 50)
				game->object->objects[i]->frame = 2;
			if (game->object->tick == 75)
				game->object->objects[i]->frame = 3;
			if (game->object->tick == 120)
			{
				game->object->objects[i]->frame = 0;
				game->object->tick = 0;
			}
		}
	}
	ft_render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->mlx_img, 0, 0);
	ft_fps(game);
	// mlx_destroy_image(game->mlx, game->img->mlx_img);
	// free(game->img);
	// game->img = NULL;
	return (0);
}
