/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:40 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/30 21:32:55 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_color_floor(t_game *game, t_render *render)
{
	int	x;

	x = -1;
	while (++x < screenWidth)
	{
		render->tex_x = (int)(SPRITE_SIZE * (render->floor_x
			- (int)render->floor_x) * 1) % SPRITE_SIZE;
		render->tex_y = (int)(SPRITE_SIZE * (render->floor_y
			- (int)render->floor_y) * 1) % SPRITE_SIZE;
		render->floor_x += render->step_x;
		render->floor_y += render->step_y;
		render->color = ft_get_pixel(game->assets->floor, render->tex_x, 
			render->tex_y);
		ft_fog(render->row_dist, &render->color);
		ft_put_pixel(game->img, x, render->y, render->color);
		render->color = ft_get_pixel(game->assets->ceil, render->tex_x,
			render->tex_y);
		ft_fog(render->row_dist, &render->color);
		ft_put_pixel(game->img, x, screenHeight - render->y - 1,
			render->color);
	}
}

void	ft_floor(t_game *game, t_render *render)
{

	render->y = 0;
	t_vector	dir0;
	t_vector	dir1;
	dir0.x = game->player->dir->x - game->plane->x;
	dir0.y = game->player->dir->y - game->plane->y;
	dir1.x = game->player->dir->x + game->plane->x;
	dir1.y = game->player->dir->y + game->plane->y;
	while (render->y < screenHeight)
	{
		render->row_dist = (double)(screenHeight * 0.5)
			/ (double)(render->y - screenHeight / 2);
		render->step_x = render->row_dist * (dir1.x - dir0.x) / screenWidth;
		render->step_y = render->row_dist * (dir1.y - dir0.y) / screenWidth;
		render->floor_x = game->player->pos->x + render->row_dist * dir0.x;
		render->floor_y = game->player->pos->y + render->row_dist * dir0.y;
		ft_color_floor(game, render);
		render->y++;
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

void	ft_draw_sky_floor(t_game *game, t_render *render)
{
	render->y = render->end;
	while (render->y < screenHeight)
	{
		ft_put_pixel(game->img, render->x, render->y,
			0x4C5270); // SOL
		ft_put_pixel(game->img, render->x, screenHeight - render->y - 1,
			0x00D1D1); // CIEL
		render->y++;
	}
}

void	ft_wall_color(t_game *game, t_ray *ray, t_render *render)
{
	if (render->color == -1)
	{
		render->color = ft_get_pixel(game->assets->door, \
				render->sprite_x, render->sprite_y);
		return ;
	}
	render->color = ft_get_pixel(game->assets->wall_S, \
		render->sprite_x, render->sprite_y);
	if (ray->side == 1 && ray->dir->y < 0)
		render->color = ft_get_pixel(game->assets->wall_W, \
			render->sprite_x, render->sprite_y);
	else if (ray->side == 1 && ray->dir->y > 0)
		render->color = ft_get_pixel(game->assets->wall_E, \
			render->sprite_x, render->sprite_y);
	else if (ray->side == 0 && ray->dir->x > 0)
		render->color = ft_get_pixel(game->assets->wall_N,\
			render->sprite_x, render->sprite_y);
	ft_fog(render->perp_wall_dist, &render->color);
	
	
}
