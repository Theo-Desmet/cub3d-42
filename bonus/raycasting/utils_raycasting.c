/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:07:00 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/20 16:50:07 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	ft_clampf(double x, double low, double high)
{
	if (x > high)
		x = high;
	if (x < low)
		x = low;
	return (x);
}

void	ft_prepare_ray(t_game *game, int x)
{
	t_ray	*ray;

	ray = game->ray;
	ray->camera_x = 2.0 * (double)x / (double)S_WIDTH - 1.0;
	ray->dir->x = game->player->dir->x + game->plane->x * ray->camera_x;
	ray->dir->y = game->player->dir->y + game->plane->y * ray->camera_x;
	ray->ddx = fabs(1 / ray->dir->x);
	ray->ddy = fabs(1 / ray->dir->y);
	ray->pos->x = game->player->pos->x;
	ray->pos->y = game->player->pos->y;
	ray->map_x = (int)ray->pos->x;
	ray->map_y = (int)ray->pos->y;
	ray->hit = 0;
}

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

void	ft_get_wall_tex(t_ray *ray, t_render *render, t_game *game)
{
	if (render->wall_tex)
		return ;
	render->wall_tex = game->assets->wall_e;
	if (ray->side == 1 && ray->dir->y < 0)
		render->wall_tex = game->assets->wall_s;
	else if (ray->side == 1 && ray->dir->y > 0)
		render->wall_tex = game->assets->wall_n;
	else if (ray->side == 0 && ray->dir->x > 0)
		render->wall_tex = game->assets->wall_w;
}

void	ft_particular_wall_hit(t_game *game, t_render *render, t_ray *ray)
{
	int	**map;

	map = game->map->map;
	render->wall_tex = NULL;
	if (ray->side == 1 && map[ray->map_y - ray->step_y][ray->map_x] == 3)
		render->wall_tex = game->assets->door_frame;
	else if (ray->side == 0 && map[ray->map_y][ray->map_x - ray->step_x] == 3)
		render->wall_tex = game->assets->door_frame;
	else if (ray->side == 1 && map[ray->map_y - ray->step_y][ray->map_x] == 4)
		render->wall_tex = game->assets->door_frame;
	else if (ray->side == 0 && map[ray->map_y][ray->map_x - ray->step_x] == 4)
		render->wall_tex = game->assets->door_frame;
	ray->hit = 1;
}
