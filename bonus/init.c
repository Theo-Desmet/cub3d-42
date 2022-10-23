/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:38:20 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/23 22:34:12 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_img	*ft_init_img(void *mlx, char *path, int width, int height)
{
	t_img	*img;
	int		size;

	size = SP_SIZE;
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
	img->height = height;
	img->width = width;
	return (img);
}

t_assets	*ft_init_assets(t_game *game, void *mlx)
{
	t_assets	*asset;

	asset = malloc(sizeof(t_assets));
	if (!asset)
		return (NULL);
	asset->wall_e = ft_init_img(mlx, game->textures_path[0], SP_SIZE, SP_SIZE);
	asset->wall_n = ft_init_img(mlx, game->textures_path[2], SP_SIZE, SP_SIZE);
	asset->wall_s = ft_init_img(mlx, game->textures_path[3], SP_SIZE, SP_SIZE);
	asset->wall_w = ft_init_img(mlx, game->textures_path[1], SP_SIZE, SP_SIZE);
	asset->ceil = ft_init_img(mlx, "assets/ceiling4.xpm", SP_SIZE, SP_SIZE);
	asset->floor = ft_init_img(mlx, "assets/floor2.xpm", SP_SIZE, SP_SIZE);
	asset->gun = ft_init_img(mlx, "assets/gunFrame.xpm",
			SP_SIZE * 5, SP_SIZE * 5);
	asset->obj = ft_init_img(mlx, "assets/barrel3.xpm",
			SP_SIZE * 4, SP_SIZE * 4);
	asset->door = ft_init_img(mlx, "assets/door.xpm", SP_SIZE, SP_SIZE);
	asset->light = ft_init_img(mlx, "assets/greenlight.xpm", SP_SIZE, SP_SIZE);
	asset->door_frame = ft_init_img(mlx, "assets/door_frame.xpm",
			SP_SIZE, SP_SIZE);
	if (!asset->wall_e || !asset->wall_n || !asset->wall_s || !asset->wall_w
		|| !asset->ceil || !asset->floor || !asset->gun
		|| !asset->door || !asset->obj || !asset->light || !asset->door_frame)
		return (ft_putstr_fd(ERROR_ASSETS, 2),
			ft_free_assets(asset, mlx), NULL);
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

t_player	*ft_init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->dir = ft_init_vector(0, 0);
	player->pos = ft_init_vector(0, 0);
	player->rot_speed = ROTATE_SPEED;
	player->walk_speed = MOVING_SPEED;
	if (!player->dir || !player->pos)
		return (ft_free_player(player), NULL);
	return (player);
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
