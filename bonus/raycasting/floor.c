/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:40 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/09 11:06:37 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_color_floor(t_game *game, t_render *render)
{
	int		x;
	double	floor_x;
	double	floor_y;

	x = -1;
	floor_x = render->floor_x;
	floor_y = render->floor_y;
	while (++x < S_WIDTH)
	{
		render->tex_x = ft_modulo((int)(SP_SIZE * (floor_x
						- (int)floor_x)));
		render->tex_y = ft_modulo((int)(SP_SIZE * (floor_y
						- (int)floor_y)));
		floor_x += render->step_x;
		floor_y += render->step_y;
		if ((floor_x >= game->map->width || floor_y >= game->map->height
				|| floor_x < 0 || floor_y < 0))
			continue ;
		if (render->color != FOG_COLOR)
			render->color = ft_get_pixel(game->assets->floor, render->tex_x,
					render->tex_y);
		ft_fog(render->row_dist, &render->color);
		ft_put_pixel(game->img, x, render->y, render->color);
	}
}

void	hehe(t_game *game, t_render *render)
{
	int	x;

	x = -1;
	while (++x < S_WIDTH)
	{
		ft_put_pixel(game->img, x, S_HEIGHT - render->y - 1, FOG_COLOR);
		ft_put_pixel(game->img, x, render->y, FOG_COLOR);
	}
}

void	ft_color_ceil(t_game *game, t_render *render)
{
	int		x;
	double	floor_x;
	double	floor_y;

	x = -1;
	floor_x = render->floor_x;
	floor_y = render->floor_y;
	while (++x < S_WIDTH)
	{
		render->tex_x = ft_modulo((int)(SP_SIZE * (floor_x
						- (int)floor_x)));
		render->tex_y = ft_modulo((int)(SP_SIZE * (floor_y
						- (int)floor_y)));
		floor_x += render->step_x;
		floor_y += render->step_y;
		if ((floor_x >= game->map->width || floor_y >= game->map->height
				|| floor_x < 0 || floor_y < 0))
			continue ;
		if (render->color != FOG_COLOR)
			render->color = ft_get_pixel(game->assets->ceil, render->tex_x,
					render->tex_y);
		ft_fog(render->row_dist, &render->color);
		ft_put_pixel(game->img, x, S_HEIGHT - render->y - 1,
			render->color);
	}
}

void	ft_floor(t_game *game, t_render *render)
{
	t_vector	dir0;
	t_vector	dir1;

	dir0.x = game->player->dir->x - game->plane->x;
	dir0.y = game->player->dir->y - game->plane->y;
	dir1.x = game->player->dir->x + game->plane->x;
	dir1.y = game->player->dir->y + game->plane->y;
	render->y = S_HEIGHT;
	while (render->y > (S_HEIGHT / 2))
	{
		render->row_dist = (double)(S_HEIGHT / 2)
			/ (double)(render->y - S_HEIGHT / 2);
		if (render->row_dist > SHADING_DISTANCE)
			hehe(game, render);
		else
		{
			render->step_x = render->row_dist * (dir1.x - dir0.x) / S_WIDTH;
			render->step_y = render->row_dist * (dir1.y - dir0.y) / S_WIDTH;
			render->floor_x = game->player->pos->x + render->row_dist * dir0.x;
			render->floor_y = game->player->pos->y + render->row_dist * dir0.y;
			ft_color_floor(game, render);
			ft_color_ceil(game, render);
		}
		render->y--;
	}
}

void	ft_floor_wall(t_ray *ray, t_render *render)
{
	if (ray->side == 0 && ray->dir->x > 0)
	{
		render->floor_x = (double)ray->map_x;
		render->floor_y = (double)ray->map_y + render->wall_x;
	}
	else if (ray->side == 0 && ray->dir->x < 0)
	{
		render->floor_x = (double)ray->map_x + 1.0;
		render->floor_y = (double)ray->map_y + render->wall_x;
	}
	else if (ray->side == 1 && ray->dir->y > 0)
	{
		render->floor_x = (double)ray->map_x + render->wall_x;
		render->floor_y = (double)ray->map_y;
	}
	else
	{
		render->floor_x = (double)ray->map_x + render->wall_x;
		render->floor_y = (double)ray->map_y + 1.0;
	}
}
