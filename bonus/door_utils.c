/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:06:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/18 16:12:16 by bbordere         ###   ########.fr       */
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
		render->wall_tex = game->assets->door_frame;
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
		render->wall_tex = game->assets->door_frame;
	}	
}

void	ft_door_handler(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->nb_doors)
	{
		game->doors[i]->factor -= DOOR_SPEED * game->doors[i]->state;
		if (game->doors[i]->factor > 1.0)
			game->doors[i]->factor = 1;
		if (game->doors[i]->factor < 0.0)
			game->doors[i]->factor = 0.0;
	}
}

t_door	*ft_init_door(int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	if (!door)
		return (NULL);
	door->x = x;
	door->y = y;
	door->factor = 0;
	door->state = 1;
	return (door);
}

t_door	**ft_alloc_doors(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
			if (game->map->map[i][j] == 3)
				game->nb_doors++;
	}
	game->doors = (t_door **)ft_calloc(game->nb_doors + 1, sizeof(t_door *));
	if (!game->doors)
		return (NULL);
	return (game->doors);
}
