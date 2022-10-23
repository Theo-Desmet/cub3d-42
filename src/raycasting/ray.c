/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:43:33 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/23 19:20:34 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_get_wall_tex(t_ray *ray, t_render *render, t_game *game)
{
	render->wall_tex = game->assets->wall_e;
	if (ray->side == 1 && ray->dir->y < 0)
		render->wall_tex = game->assets->wall_s;
	else if (ray->side == 1 && ray->dir->y > 0)
		render->wall_tex = game->assets->wall_n;
	else if (ray->side == 0 && ray->dir->x > 0)
		render->wall_tex = game->assets->wall_w;
}

void	ft_wall_hit(t_ray *ray, t_game *game)
{
	while (!ray->hit)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->ddx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->ddy;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map[ray->map_y][ray->map_x] == 1
			|| game->map->map[ray->map_y][ray->map_x] == 8)
			ray->hit = 1;
	}
}

void	ft_prepare_proj(t_game *game, t_render *render)
{
	t_ray	*ray;

	ray = game->ray;
	if (game->ray->side == 0)
		render->perp_wall_dist = game->ray->sidedist_x - game->ray->ddx;
	else
		render->perp_wall_dist = game->ray->sidedist_y - game->ray->ddy;
	render->height_line = ((int)(S_HEIGHT / render->perp_wall_dist));
	render->start = - (render->height_line) / 2 + S_HEIGHT / 2;
	render->end = render->height_line / 2 + S_HEIGHT / 2;
	if (render->start < 0)
		render->start = 0;
	if (render->end >= S_HEIGHT)
		render->end = S_HEIGHT;
	if (render->end < 0)
		render->end = S_HEIGHT;
	if (game->ray->side == 0)
		render->wall_x = ray->pos->y + render->perp_wall_dist * ray->dir->y;
	else
		render->wall_x = ray->pos->x + render->perp_wall_dist * ray->dir->x;
	render->wall_x -= floor(render->wall_x);
	render->sprite_x = (int)(render->wall_x * (double)SP_SIZE);
}

void	ft_wall_proj(t_ray *ray, t_render *render, t_game *game)
{
	ft_prepare_proj(game, render);
	if (ray->side == 0 && ray->dir->x > 0.0)
		render->sprite_x = SP_SIZE - render->sprite_x - 1;
	if (ray->side == 1 && ray->dir->y < 0.0)
		render->sprite_x = SP_SIZE - render->sprite_x - 1;
	render->y = render->start;
	ft_get_wall_tex(ray, render, game);
	while (render->y < render->end)
	{
		render->sprite_y = (render->y * 2 - S_HEIGHT + render->height_line)
			* (SP_SIZE / 2) / render->height_line;
		render->color = ft_get_pixel(render->wall_tex, render->sprite_x,
				render->sprite_y);
		ft_put_pixel(game->img, render->x, render->y, render->color);
		render->y++;
	}
}
