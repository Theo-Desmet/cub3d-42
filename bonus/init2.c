/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/21 16:21:49 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_free_all(t_game *game)
{
	ft_free_visual(game);
	if (game->plane)
		free(game->plane);
	if (game->textures_path)
		ft_free_textures(game);
	if (game->map)
		ft_free_map(game, game->map->height - 1);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->fps)
		free(game->fps);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

t_map	*ft_alloc_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_putstr_fd("Error while init map !\n", 2), NULL);
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

t_game	*ft_init_primary(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), NULL);
	game->map = ft_alloc_map();
	game->textures_path = ft_calloc(4, sizeof(char *));
	game->player = ft_init_player();
	game->enemy = ft_init_enemy(game);
	game->plane = ft_init_vector(1, 0);
	if (!game->map || !game->textures_path || !game->player || !game->plane
		|| !game->enemy)
		return (ft_free_all(game), NULL);
	return (game);
}

t_game	*ft_init_game(int ac, char **av)
{
	t_game	*game;

	game = ft_alloc_game();
	if (!game || !ft_init_primary(game))
		return (ft_putstr_fd("Error while init the game !\n", 2), NULL);
	if (!ft_parsing(game, ac, av))
		return (ft_free_all(game), NULL);
	ft_update_player(game);
	srand(time(NULL));
	ft_spawn_enemy(game);
	game->assets = ft_init_assets(game, game->mlx);
	if (!game->assets)
		return (ft_putstr_fd("Error while init assets !\n", 2),
			ft_free_all(game), NULL);
	game->ray = ft_init_ray();
	game->object = ft_init_obj(game);
	game->img = ft_init_img(game->mlx, NULL, S_WIDTH, S_HEIGHT);
	game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "cub3D");
	game->frame = 50;
	game->doors = ft_get_doors(game);
	if (!game->ray || !game->object || !game->img
		|| !game->win || !game->doors)
		return (ft_putstr_fd("Error while init the game !\n", 2),
			ft_free_all(game), NULL);
	return (game);
}
