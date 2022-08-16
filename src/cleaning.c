/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:35:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/16 10:43:23 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_assets(t_assets *assets, void *mlx)
{
	if (assets->wall_E)
		mlx_destroy_image(mlx, assets->wall_E->mlx_img);
	if (assets->wall_N)
		mlx_destroy_image(mlx, assets->wall_N->mlx_img);
	if (assets->wall_S)
		mlx_destroy_image(mlx, assets->wall_S->mlx_img);
	if (assets->wall_W)
		mlx_destroy_image(mlx, assets->wall_W->mlx_img);
	free(assets->wall_E);
	free(assets->wall_N);
	free(assets->wall_S);
	free(assets->wall_W);
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
