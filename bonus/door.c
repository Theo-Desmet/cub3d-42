/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:23:17 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/18 21:31:40 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	factor = 0;

t_door	*ft_get_cur_door(t_game *game, int x, int y)
{
	int	i;

	i = -1;
	while (++i < game->nb_doors)
		if (game->doors[i]->x == x && game->doors[i]->y == y)
			return (game->doors[i]);
	return (NULL);
}

void	ft_harbor(t_ray *ray, t_render *render, t_game *game)
{
	t_door	*door;

	door = ft_get_cur_door(game, ray->map_x, ray->map_y);
	if ((int)door->factor == 0 && game->map->map[ray->map_y][ray->map_x] == 4)
		game->map->map[ray->map_y][ray->map_x] = 3;
	ray->hit = 1;
	if (ray->side == 1)
	{
		render->perp_wall_dist = (ray->map_y - game->ray->pos->y + (1 - ray->step_y)) / ray->dir->y;
		render->wall_x = game->ray->pos->x + render->perp_wall_dist * ray->dir->x;
		render->wall_x -= floor(render->wall_x);
		if (ray->sidedist_y  < ray->sidedist_x)
			ray->hit = 0;
		else
		{
			ray->map_x += ray->step_x;
			ray->side = 0;
			render->wall_tex = game->assets->ceil;
		}
	}
	else
	{
		render->perp_wall_dist = (ray->map_x - ray->pos->x + (1 - ray->step_x)) / ray->dir->x;
		render->wall_x = ray->pos->y + render->perp_wall_dist * ray->dir->y;
		render->wall_x -= floor(render->wall_x);
		if (ray->sidedist_x  < ray->sidedist_y)
			ray->hit = 0;
		else
		{
			ray->map_y += ray->step_y;
			ray->side = 1;
			render->wall_tex = game->assets->ceil;
		}
	}
}

void	ft_update_x_offset(t_ray *ray, t_render *render, t_game *game, t_door *door)
{
		render->y_offset = 0.5 * ray->step_y;
		render->perp_wall_dist = (ray->map_y - ray->pos->y + render->y_offset
				+ (1 - ray->step_y) / 2) / ray->dir->y;
		render->wall_x = ray->pos->x + render->perp_wall_dist * ray->dir->x;
		render->wall_x -= floor(render->wall_x);
		if (ray->sidedist_y - (ray->ddy / 2) < ray->sidedist_x)
		{
			if (1.0 - render->wall_x < door->factor)
			{
				ray->hit = 0;
				render->y_offset = 0.0;
			}
		}
		else
		{
			ray->map_x += ray->step_x;
			ray->side = 0;
			render->wall_tex = game->assets->ceil;
			render->y_offset = 0.0;
		}
}

void	ft_update_y_offset(t_ray *ray, t_render *render, t_game *game, t_door *door)
{
	render->x_offset = 0.5 * ray->step_x;
	render->perp_wall_dist = (ray->map_x - ray->pos->x + render->x_offset
			+ (1 - ray->step_x) / 2) / ray->dir->x;
	render->wall_x = ray->pos->y + render->perp_wall_dist * ray->dir->y;
	render->wall_x -= floor(render->wall_x);
	if (ray->sidedist_x - (ray->ddx / 2) < ray->sidedist_y)
	{
		if (1.0 - render->wall_x < door->factor)
		{
			ray->hit = 0;
			render->x_offset = 0.0;
		}
	}
	else
	{
		ray->map_y += ray->step_y;
		ray->side = 1;
		render->wall_tex = game->assets->ceil;
		render->x_offset = 0.0;
	}	
}

void	ft_door_hit(t_ray *ray, t_render *render, t_game *game)
{
	t_door	*door;

	door = ft_get_cur_door(game, ray->map_x, ray->map_y);
	ray->hit = 1;
	render->wall_tex = game->assets->door;
	if (ray->side == 1)
		ft_update_x_offset(ray, render, game, door);
	else
		ft_update_y_offset(ray, render, game, door);
	if ((int)door->factor == 1 && game->map->map[ray->map_y][ray->map_x] == 3)
		game->map->map[ray->map_y][ray->map_x] = 4;
}
