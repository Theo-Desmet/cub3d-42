/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/15 11:02:18 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_dir(t_game *game)
{
	game->forward = false;
	game->backward = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;
}

void	ft_update_heading(t_game *game, double x, double y)
{
	double half_fov;

	half_fov = FOV / 2;
	game->player->dir->x = x;
	game->player->dir->y = y;
	game->plane->x = -y * ((half_fov * M_PI) / 180);
	game->plane->y = x * ((half_fov * M_PI) / 180);
}

void	ft_update_player(t_game *game)
{
	game->player->pos->x = (double)game->player->parsed_x + 0.5;
	game->player->pos->y = (double)game->player->parsed_y + 0.5;
	if (game->player->heading == 'W')
		ft_update_heading(game, -1.0, 0.0);
	else if (game->player->heading == 'E')
		ft_update_heading(game, 1.0, 0.0);
	else if (game->player->heading == 'S')
		ft_update_heading(game, 0.0, 1.0);
	else
		ft_update_heading(game, 0.0, -1.0);
}

t_game	*ft_init_game(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), NULL);
	game->img = ft_init_img(game->mlx, NULL, screenWidth, screenHeight);
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3D");
	game->map = malloc(sizeof(t_map));
	game->textures_path = malloc(4 * sizeof(char *));
	game->map->width = 0;
	game->map->height = 0;
	game->plane = ft_init_vector(1, 0);
	game->player = ft_init_player();
	ft_parsing(game, ac, av);
	ft_update_player(game);
	game->assets = ft_init_assets(game, game->mlx);
	game->ray = ft_init_ray();
	ft_init_dir(game);
	if (!game->win || !game->assets || !game->player || !game->ray
		|| !game->plane || !game->textures_path)
		return (ft_free_all(game), NULL);
	return (game);
}
