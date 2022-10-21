/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:02:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/21 14:23:26 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		free(game->textures_path[i++]);
	free(game->textures_path);
}

void	ft_update_heading(t_game *game, double x, double y)
{
	game->player->dir->x = x;
	game->player->dir->y = y;
	game->plane->x = -y * (((FOV / 2) * M_PI) / 180);
	game->plane->y = x * (((FOV / 2) * M_PI) / 180);
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

// void	ft_fill_error_msg(char **arr)
// {
// 	arr[NO_FILE] = ft_strdup("bad file: please add an file with .cub"
// 			" extension\n");
// 	arr[TOO_MANY_FILE] = ft_strdup("bad file: too many files, please use"
// 			" only one\n");
// 	arr[BAD_EXTENSION] = ft_strdup("bad extension file: filename need .cub"
// 			" extension\n");
// 	arr[BAD_FORMAT] = ft_strdup("bad filename: please use a valid filename\n");
// 	arr[NOT_FOUND] = ft_strdup("bad filename: file not found\n");
	
// 	arr[INVALID_SYNTAX] = ft_strdup(": use or redefine of an invalid syntax\n");
// 	arr[INVALID_CHAR] = ft_strdup(": use of an invalid char on map\n");
// 	arr[MULTI_SPAWN] = ft_strdup(": redefine of spawn, please use only one\n");
// 	arr[NO_SPAWN] = ft_strdup("error in file: no spawn in map\n");
// 	arr[COPY_ERROR] = ft_strdup("error during the copy of the map\n");
// 	arr[INVALID_HEADER] = ft_strdup("error in file: invalid line in head\n");
// }

void	ft_dda(t_ray *ray)
{
	if (ray->dir->x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->pos->x - ray->map_x) * ray->ddx;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->pos->x) * ray->ddx;
	}
	if (ray->dir->y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->pos->y - ray->map_y) * ray->ddy;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->pos->y) * ray->ddy;
	}
}
