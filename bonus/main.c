/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:16:13 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/16 11:45:55 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_parsing(t_game *game, int argc, char **argv);

int **worldMap = NULL;


int main(int ac, char **av)
{
	t_game	*game;

	game = ft_init_game(ac, av);
	if (!game)
		exit(EXIT_FAILURE);
	mlx_hook(game->win, 2, 1L, ft_key_down, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_up, game);
	mlx_hook(game->win, 17, 1L, ft_free_all, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	ft_free_all(game);
	return (0);
}