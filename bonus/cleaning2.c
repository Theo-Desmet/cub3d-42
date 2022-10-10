/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:51:12 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/08 12:51:44 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_free_sprite(t_game *game, t_sprite *sprite)
{
	if (sprite->texture)
	{
		mlx_destroy_image(game->mlx, sprite->texture->mlx_img);
		free(sprite->texture);
	}
	if (sprite->pos)
		free(sprite->pos);
	if (sprite->last_pos)
		free(sprite->last_pos);
	free(sprite);
}

void	ft_free_obj_tab(t_game *game, t_object *obj)
{
	int	i;

	i = 0;
	while (i < obj->nb_obj)
	{
		if (obj->objects[i])
			ft_free_sprite(game, obj->objects[i]);
		i++;
	}
	free(obj->objects);
	obj->objects = NULL;
}

void	ft_free_obj(t_game *game, t_object *obj)
{
	if (obj->zbuff)
		free(obj->zbuff);
	if (obj->dist)
		free(obj->dist);
	if (obj->objects)
		ft_free_obj_tab(game, obj);
	if (obj->order)
		free(obj->order);
	free(obj);
}

void	ft_free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		free(game->textures_path[i++]);
	free(game->textures_path);
}

void	ft_free_visual(t_game *game)
{
	if (game->ray)
		ft_free_ray(game->ray);
	if (game->assets)
		ft_free_assets(game->assets, game->mlx);
	if (game->player)
		ft_free_player(game->player);
	if (game->object)
		ft_free_obj(game, game->object);
	if (game->doors)
		ft_free_tab((void **)game->doors);
	if (game->img)
	{
		mlx_destroy_image(game->mlx, game->img->mlx_img);
		free(game->img);
	}
}
