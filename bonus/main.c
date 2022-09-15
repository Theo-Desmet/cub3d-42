/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:16:13 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/15 14:14:20 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_parsing(t_game *game, int argc, char **argv);

int	test(int x, int y, t_game *game)
{
	static int	last_x;
	
	mlx_mouse_move(game->mlx, game->win, screenWidth / 2, screenHeight / 2);
	if (last_x != x)
	{
		if (last_x > x)
		{
			game->rotate_right = false;
			game->rotate_left = true;
		}
		else if (last_x < x)
		{
			game->rotate_left = false;
			game->rotate_right = true;
		}
		last_x = x;
	}
	else
	{
		game->rotate_right = false;
		game->rotate_left = false;
	}
	return (1);
}

int main(int ac, char **av)
{
	t_game	*game;

	game = ft_init_game(ac, av);
	if (!game)
		exit(EXIT_FAILURE);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_hook(game->win, 2, 1L, ft_key_down, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_up, game);
	mlx_hook(game->win, 17, 1L, ft_free_all, game);
	mlx_hook(game->win, 06, 1L << 6, test, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	ft_free_all(game);
	return (0);
}