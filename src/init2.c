/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/23 20:07:05 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*ft_alloc_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(t_game));
	return (game);
}

t_map	*ft_alloc_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_putstr_fd(ERROR_MAP, 2), NULL);
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

t_game	*ft_init_game(int ac, char **av)
{
	t_game	*game;

	game = ft_alloc_game();
	if (!game)
		return (ft_putstr_fd(ERROR_GAME, 2), NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd(ERROR_MLX, 2), free(game), NULL);
	game->map = ft_alloc_map();
	game->textures_path = ft_calloc(4, sizeof(char *));
	game->player = ft_init_player();
	game->plane = ft_init_vector(1, 0);
	if (!game->map || !game->textures_path || !game->player
		|| !game->plane || !ft_parsing(game, ac, av))
		return (ft_free_all(game), NULL);
	game->assets = ft_init_assets(game, game->mlx);
	if (!game->assets)
		return (ft_free_all(game), NULL);
	game->ray = ft_init_ray();
	game->img = ft_init_img(game->mlx, NULL, S_WIDTH, S_HEIGHT);
	game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "cub3D");
	if (!game->ray || !game->img || !game->win)
		return (ft_free_all(game), NULL);
	return (game);
}
