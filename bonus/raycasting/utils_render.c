/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:05:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/09 11:40:30 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_sprite(t_object *obj)
{
	int		i;
	int		j;
	int		temp;

	i = -1;
	while (++i < obj->nb_obj)
	{
		j = -1;
		while (++j + 1 < obj->nb_obj)
		{
			if (obj->dist[j + 1] > obj->dist[j])
			{
				ft_swap(&obj->dist[j + 1], &obj->dist[j]);
				temp = obj->order[j + 1];
				obj->order[j + 1] = obj->order[j];
				obj->order[j] = temp;
			}
		}
	}
}

int	ft_modulo(int x)
{
	if (x == SP_SIZE)
		return (0);
	return (x);
}

void	ft_wall_color(t_game *game, t_ray *ray, t_render *render)
{
	render->color = ft_get_pixel(game->assets->wall_s,
			render->sprite_x, render->sprite_y);
	if (ray->side == 1 && ray->dir->y < 0)
		render->color = ft_get_pixel(game->assets->wall_w,
				render->sprite_x, render->sprite_y);
	else if (ray->side == 1 && ray->dir->y > 0)
		render->color = ft_get_pixel(game->assets->wall_e,
				render->sprite_x, render->sprite_y);
	else if (ray->side == 0 && ray->dir->x > 0)
		render->color = ft_get_pixel(game->assets->wall_n,
				render->sprite_x, render->sprite_y);
	ft_fog(render->perp_wall_dist, &render->color);
}
