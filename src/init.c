/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:38:20 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/29 11:24:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_init_img(void *mlx, char *path, int width, int height)
{
	t_img	*img;
	int		size;

	size = SPRITE_SIZE;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	if (path)
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size, &size);
	else
		img->mlx_img = mlx_new_image(mlx, width, height);
	if (!img->mlx_img)
		return (free(img), NULL);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		return (free(img), NULL);
	img->width = width;
	img->height = height;
	return (img);
}

t_assets	*ft_init_assets(t_game *game, void *mlx)
{
	t_assets	*asset;

	asset = malloc(sizeof(t_assets));
	if (!asset)
		return (NULL);
	asset->wall_E = ft_init_img(mlx, game->textures_path[0],
			SPRITE_SIZE, SPRITE_SIZE);
	asset->wall_N = ft_init_img(mlx, game->textures_path[2],
			SPRITE_SIZE, SPRITE_SIZE);
	asset->wall_S = ft_init_img(mlx, game->textures_path[3],
			SPRITE_SIZE, SPRITE_SIZE);
	asset->wall_W = ft_init_img(mlx, game->textures_path[1],
			SPRITE_SIZE, SPRITE_SIZE);
	if (!asset->wall_E || !asset->wall_N || !asset->wall_S || !asset->wall_W)
		return (ft_free_assets(asset, mlx), NULL);
	return (asset);
}

t_vector	*ft_init_vector(double x, double y)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_ray	*ft_init_ray(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->camera_x = 0.0;
	ray->ddx = 0.0;
	ray->ddy = 0.0;
	ray->sidedist_x = 0.0;
	ray->sidedist_y = 0.0;
	ray->hit = 0;
	ray->side = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->pos = ft_init_vector(0.0, 0.0);
	ray->dir = ft_init_vector(0.0, 0.0);
	if (!ray->dir || !ray->pos)
		return (ft_free_ray(ray), NULL);
	return (ray);
}
