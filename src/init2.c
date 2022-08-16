/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/16 11:00:43 by bbordere         ###   ########.fr       */
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

t_game	*ft_init_game(void)
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
	game->assets = ft_init_assets(game->mlx);
	game->player = ft_init_player();
	game->ray = ft_init_ray();
	game->plane = ft_init_vector(1, 0); // fov=1=90 N : y=fov, S : -fov, E x=fov, W x=-fov 
	ft_init_dir(game);
	if (!game->win || !game->assets || !game->player || !game->ray
		|| !game->plane)
		return (ft_free_all(game), NULL);
	return (game);
}
