/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:34 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/27 18:57:59 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_down(int keycode, t_game *game)
{
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

int	ft_key_up(int keycode, t_game *game)
{
	if (keycode == 'z')
		game->forward = false;
	if (keycode == 'm')
		factor = 1;
	if (keycode == 'k')
		factor = 0;
	if (keycode == 'h')
		game->opening *= -1;
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
	if (factor > 1.0)
		factor = 1;
	if (factor < 0.0)
		factor = 0.0;
	factor -= 0.008 * game->opening;
	game->img = ft_init_img(game->mlx, NULL, screenWidth, screenHeight);
	ft_render(game);
	mlx_do_sync(game->mlx);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_put_image_to_window(game->mlx, game->win, game->img->mlx_img, 0, 0);
	mlx_destroy_image(game->mlx, game->img->mlx_img);
	free(game->img);
	game->img = NULL;
	return (0);
}
