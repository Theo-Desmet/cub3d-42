/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:43:33 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/27 18:54:19 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_prepare_ray(t_game *game, int x)
{
	t_ray	*ray;

	ray = game->ray;
	ray->camera_x = 2.0 * (double)x / (double)screenWidth - 1.0;
	ray->dir->x = game->player->dir->x + game->plane->x * ray->camera_x;
	ray->dir->y = game->player->dir->y + game->plane->y * ray->camera_x;

	ray->ddx = sqrt(1.0 + pow(ray->dir->y, 2.0) / pow(ray->dir->x, 2.0));
	ray->ddy = sqrt(1.0 + pow(ray->dir->x, 2.0) / pow(ray->dir->y, 2.0));

	// ray->ddx = fabs(1 / ray->dir->x);
	// ray->ddy = fabs(1 / ray->dir->y);

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

double	factor = 0.5;

void	ft_door_hit(t_ray *ray, t_render *render, t_game *game)
{
	ray->hit = 1;
	render->wall_tex = game->assets->door;
	if (ray->side == 1)
	{
		render->y_offset = 0.5 * ray->step_y;
		render->perp_wall_dist = (ray->map_y - game->ray->pos->y + render->y_offset + (1 - ray->step_y) / 2) / ray->dir->y;
		render->wall_x = game->ray->pos->x + render->perp_wall_dist * ray->dir->x;
		render->wall_x -= floor(render->wall_x);
		if (ray->sidedist_y - (ray->ddy / 2) < ray->sidedist_x)
		{
			if (1.0 - render->wall_x <= factor)
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
	else
	{
		render->x_offset = 0.5 * ray->step_x;
		render->perp_wall_dist = (ray->map_x - game->ray->pos->x + render->x_offset + (1 - ray->step_x) / 2) / ray->dir->x;
		render->wall_x = game->ray->pos->y + render->perp_wall_dist * ray->dir->y;
		render->wall_x -= floor(render->wall_x);
		if (ray->sidedist_x - (ray->ddx / 2) < ray->sidedist_y)
		{
			if (1.0 - render->wall_x <= factor)
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
}

void	ft_get_wall_tex(t_ray *ray, t_render *render, t_game *game)
{
	if (render->wall_tex)
		return ;
	render->wall_tex = game->assets->wall_S;
	if (ray->side == 1 && ray->dir->y < 0)
		render->wall_tex = game->assets->wall_W;
	else if (ray->side == 1 && ray->dir->y > 0)
		render->wall_tex = game->assets->wall_E;
	else if (ray->side == 0 && ray->dir->x > 0)
		render->wall_tex = game->assets->wall_N;
}

void	ft_wall_hit(t_ray *ray, t_render *render, t_game *game)
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
		if (worldMap[ray->map_x][ray->map_y] == 3)
			ft_door_hit(ray, render, game);
		else if (worldMap[ray->map_x][ray->map_y] == 1)
		{
			render->wall_tex = NULL;
			if (ray->side == 1 && worldMap[ray->map_x][ray->map_y - ray->step_y] == 3)
				render->wall_tex = game->assets->ceil;
			else if (ray->side == 0 && worldMap[ray->map_x - ray->step_x][ray->map_y] == 3)
				render->wall_tex = game->assets->ceil;
			ray->hit = 1;
		}
	}
}



void	ft_prepare_proj(t_game *game, t_render *render)
{
	t_ray	*ray;

	ray = game->ray;
	// if (game->ray->side == 0)
	// 	render->perp_wall_dist = game->ray->sidedist_x - game->ray->ddx;
	// else
	// 	render->perp_wall_dist = game->ray->sidedist_y - game->ray->ddy;
	if (game->ray->side == 0)
		render->perp_wall_dist = (((double)game->ray->map_x - game->ray->pos->x + render->x_offset + (1.0 - (double)game->ray->step_x) / 2.0) / game->ray->dir->x);
	else
		render->perp_wall_dist = (((double)game->ray->map_y - game->ray->pos->y + render->y_offset + (1.0 - (double)game->ray->step_y) / 2.0) / game->ray->dir->y);
	render->height_line = ((int)(screenHeight / render->perp_wall_dist));
	render->start = - (render->height_line) / 2 + screenHeight / 2;
	render->end = render->height_line / 2 + screenHeight / 2;
	if (render->start < 0)
		render->start = 0;
	if (render->end >= screenHeight)
		render->end = screenHeight;	
	if (render->end < 0)
		render->end = screenHeight;
	// if (game->ray->side == 1)
	// 	render->wall_x = ray->pos->x + (((double)ray->map_y - ray->pos->y 
	// 		+ (1.0 - (double)ray->step_y) / 2.0) / ray->dir->y) * ray->dir->x;
	// else
	// 	render->wall_x = ray->pos->y + (((double)ray->map_x - ray->pos->x 
	// 		+ (1.0 - (double)ray->step_x) / 2.0) / ray->dir->x) * ray->dir->y;
	if (game->ray->side == 0)
		render->wall_x = ray->pos->y + render->perp_wall_dist * ray->dir->y;
	else
		render->wall_x = ray->pos->x + render->perp_wall_dist * ray->dir->x;

	render->wall_x -= floor(render->wall_x);
	render->sprite_x = (int)(render->wall_x * (double)SPRITE_SIZE);
	if (render->wall_tex == game->assets->door)
		render->wall_x += factor;
}

void	ft_wall_proj(t_ray *ray, t_render *render, t_game *game)
{

	ft_prepare_proj(game, render);


	// render->y = render->start;
	// while (render->y < render->end)
	// {
	// 	if (game->ray->side == 1)
	// 		ft_put_pixel(game->img, render->x, render->y, 0xCCCCCC);
	// 	else
	// 		ft_put_pixel(game->img, render->x, render->y, 0xf2f2f2);
	// 	render->y++;
	// }

	if (ray->side == 0 && ray->dir->x > 0.0)
		render->sprite_x = SPRITE_SIZE - render->sprite_x - 1;
	if (ray->side == 1 && ray->dir->y < 0.0)
		render->sprite_x = SPRITE_SIZE - render->sprite_x - 1;
	render->y = render->start;
	ft_get_wall_tex(ray, render, game);
	while (render->y < render->end)
	{
		render->sprite_y = (render->y * 2 - screenHeight + render->height_line)
			* (SPRITE_SIZE / 2) / render->height_line;
		if (render->wall_tex == game->assets->door)
			// render->color = ft_get_pixel(render->wall_tex,
			// 	render->sprite_x - ((int)(factor * SPRITE_SIZE * floor(game->player->dir->x))), render->sprite_y);
		render->color = ft_get_pixel(render->wall_tex,
				render->sprite_x - ((int)(factor * SPRITE_SIZE)), render->sprite_y);
	
		else
			render->color = ft_get_pixel(render->wall_tex,
				render->sprite_x, render->sprite_y);
		if (ray->side == 1)
			render->color = (render->color >> 1) & 0x7F7F7F;
		//ft_fog(render->perp_wall_dist, &render->color);
		ft_put_pixel(game->img, render->x, render->y, render->color);
		render->y++;
	}
	render->wall_tex = NULL;

}
