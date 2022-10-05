/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:34 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/05 15:36:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_down(int keycode, t_game *game)
{
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

int	ft_key_up(int keycode, t_game *game)
{
	if (keycode == FORWARD_KEY)
		game->forward = false;
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

int	ft_loop(t_game *game)
{
	ft_render(game);
	mlx_do_sync(game->mlx);
	mlx_put_image_to_window(game->mlx, game->win, game->img->mlx_img, 0, 0);
	ft_fps(game);

	return (0);
}
