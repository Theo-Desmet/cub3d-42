/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:06:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/06 15:12:11 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_side1(t_ray *ray, t_render *render, t_game *game)
{
	render->perp_wall_dist = (ray->map_y - game->ray->pos->y
			+ (1 - ray->step_y)) / ray->dir->y;
	render->wall_x = game->ray->pos->x + render->perp_wall_dist * ray->dir->x;
	render->wall_x -= floor(render->wall_x);
	if (ray->sidedist_y < ray->sidedist_x)
		ray->hit = 0;
	else
	{
		ray->map_x += ray->step_x;
		ray->side = 0;
		render->wall_tex = game->assets->ceil;
	}
}

void	ft_side0(t_ray *ray, t_render *render, t_game *game)
{
	render->perp_wall_dist = (ray->map_x - ray->pos->x
			+ (1 - ray->step_x)) / ray->dir->x;
	render->wall_x = ray->pos->y + render->perp_wall_dist * ray->dir->y;
	render->wall_x -= floor(render->wall_x);
	if (ray->sidedist_x < ray->sidedist_y)
		ray->hit = 0;
	else
	{
		ray->map_y += ray->step_y;
		ray->side = 1;
		render->wall_tex = game->assets->ceil;
	}	
}
