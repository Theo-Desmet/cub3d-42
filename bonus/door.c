/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:23:17 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/05 15:17:18 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_door	*ft_get_cur_door(t_game *game, int x, int y)
{
	int				i;
	static t_door	*cur;
	static int		cache_x;
	static int		cache_y;

	i = -1;
	if (cur && cache_x == x && cache_y == y)
		return (cur);
	while (++i < game->nb_doors)
	{
		if (game->doors[i]->x == x && game->doors[i]->y == y)
		{
			cur = game->doors[i];
			return (cur);
		}
	}
	return (NULL);
}

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

void	ft_harbor(t_ray *ray, t_render *render, t_game *game)
{
	t_door	*door;

	door = ft_get_cur_door(game, ray->map_x, ray->map_y);
	if ((int)door->factor == 0 && game->map->map[ray->map_y][ray->map_x] == 4)
		game->map->map[ray->map_y][ray->map_x] = 3;
	ray->hit = 1;
	if (ray->side == 1)
		ft_side1(ray, render, game);
	else
		ft_side0(ray, render, game);
}

void	ft_upd_x_off(t_ray *ray, t_render *render, t_game *game, t_door *door)
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

void	ft_upd_y_off(t_ray *ray, t_render *render, t_game *game, t_door *door)
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
		ft_upd_x_off(ray, render, game, door);
	else
		ft_upd_y_off(ray, render, game, door);
	if ((int)door->factor == 1 && game->map->map[ray->map_y][ray->map_x] == 3)
		game->map->map[ray->map_y][ray->map_x] = 4;
}
