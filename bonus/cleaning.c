/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:35:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/11 19:21:35 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_destroy_img(t_img *img, void *mlx)
{
	mlx_destroy_image(mlx, img->mlx_img);
	free(img);
	img = NULL;
}

void	ft_free_assets(t_assets *assets, void *mlx)
{
	if (assets->wall_e)
		ft_destroy_img(assets->wall_e, mlx);
	if (assets->wall_n)
		ft_destroy_img(assets->wall_n, mlx);
	if (assets->wall_s)
		ft_destroy_img(assets->wall_s, mlx);
	if (assets->wall_w)
		ft_destroy_img(assets->wall_w, mlx);
	if (assets->ceil)
		ft_destroy_img(assets->ceil, mlx);
	if (assets->floor)
		ft_destroy_img(assets->floor, mlx);
	if (assets->gun)
		ft_destroy_img(assets->gun, mlx);
	if (assets->door)
		ft_destroy_img(assets->door, mlx);
	if (assets->light)
		ft_destroy_img(assets->light, mlx);
	if (assets->obj)
		ft_destroy_img(assets->obj, mlx);
	free(assets);
}

void	ft_free_player(t_player *player)
{
	if (player->dir)
		free(player->dir);
	if (player->pos)
		free(player->pos);
	free(player);
}

void	ft_free_ray(t_ray *ray)
{
	if (ray->dir)
		free(ray->dir);
	if (ray->pos)
		free(ray->pos);
	free(ray);
}

void	ft_free_map(t_game *game, int i)
{
	if (game->map->fd_map != -1)
		close(game->map->fd_map);
	if (game->map->map)
		while (i >= 0)
			free(game->map->map[i--]);
	free(game->map->map);
	free(game->map);
}
