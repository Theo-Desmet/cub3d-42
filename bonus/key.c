/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:34 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/09 15:26:21 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_key_down(int keycode, t_game *game)
{
	if (keycode == 65505)
		game->player->walk_speed = 0.16;
	if (keycode == 65513)
		game->player->walk_speed = 0.04;
	if (keycode == 'z')
		game->forward = true;
	if (keycode == 's')
		game->backward = true;
	if (keycode == 'q')
		game->left = true;
	if (keycode == 'd')
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
	if (keycode == 'z')
		game->forward = false;
	if (keycode == 'm')
		factor = 1;
	if (keycode == 'k')
		factor = 0;
	if (keycode == ' ')
		ft_door(game);
	if (keycode == 's')
		game->backward = false;
	if (keycode == 'q')
		game->left = false;
	if (keycode == 'd')
		game->right = false;
	if (keycode == 65363)
		game->rotate_right = false;
	if (keycode == 65361)
		game->rotate_left = false;
	return (0);
}

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
	ft_render(game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_put_image_to_window(game->mlx, game->win, game->img->mlx_img, 0, 0);
	// mlx_destroy_image(game->mlx, game->img->mlx_img);
	// free(game->img);
	// game->img = NULL;
	return (0);
}
