/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:40 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/01 14:47:19 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

inline int	ft_modulo(int x)
{
	if (x == SPRITE_SIZE)
		return (0);
	return (x);
}

inline void	ft_color_floor(t_game *game, t_render *render)
{
	int	x;

	x = -1;
	while (++x < S_WIDTH)
	{
		render->tex_x = ft_modulo((int)(SPRITE_SIZE * (render->floor_x
						- (int)render->floor_x)));
		render->tex_y = ft_modulo((int)(SPRITE_SIZE * (render->floor_y
						- (int)render->floor_y)));
		render->floor_x += render->step_x;
		render->floor_y += render->step_y;
		if (render->color != FOG_COLOR)
			render->color = ft_get_pixel(game->assets->floor, render->tex_x,
					render->tex_y);
		ft_fog(render->row_dist, &render->color);
		ft_put_pixel(game->img, x, render->y, render->color);
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
	while (render->y > S_HEIGHT / 2)
	{
		render->row_dist = (double)(S_HEIGHT / 2)
			/ (double)(render->y - S_HEIGHT / 2);
		render->step_x = render->row_dist * (dir1.x - dir0.x) / S_WIDTH;
		render->step_y = render->row_dist * (dir1.y - dir0.y) / S_WIDTH;
		render->floor_x = game->player->pos->x + render->row_dist * dir0.x;
		render->floor_y = game->player->pos->y + render->row_dist * dir0.y;
		ft_color_floor(game, render);
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

void	ft_wall_color(t_game *game, t_ray *ray, t_render *render)
{
	render->color = ft_get_pixel(game->assets->wall_S,
			render->sprite_x, render->sprite_y);
	if (ray->side == 1 && ray->dir->y < 0)
		render->color = ft_get_pixel(game->assets->wall_W,
				render->sprite_x, render->sprite_y);
	else if (ray->side == 1 && ray->dir->y > 0)
		render->color = ft_get_pixel(game->assets->wall_E,
				render->sprite_x, render->sprite_y);
	else if (ray->side == 0 && ray->dir->x > 0)
		render->color = ft_get_pixel(game->assets->wall_N,
				render->sprite_x, render->sprite_y);
	ft_fog(render->perp_wall_dist, &render->color);
}
