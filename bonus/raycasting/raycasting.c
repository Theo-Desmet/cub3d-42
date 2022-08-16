/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:49:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/16 15:09:10 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdbool.h>

int	ft_free_all(t_game *game)
{
	free(game->img);
	if (game->assets)
		ft_free_assets(game->assets, game->mlx);
	if (game->player)
		ft_free_player(game->player);
	if (game->ray)
		ft_free_ray(game->ray);
	if (game->plane)
		free(game->plane);
	if (game->object)
		ft_free_obj(game->object);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

t_render	*ft_init_render(void)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	render->end = 0;
	render->start = 0;
	render->x = 0;
	render->y = 0;
	render->color = 0;
	render->sprite_x = 0;
	render->sprite_y = 0;
	render->wall_x = 0;
	return (render);
}

void	ft_sprite_cast(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->object->nb_obj)
	{
		game->object->order[i] = i;
		game->object->dist[i] = (pow(game->player->pos->x
					- game->object->objects[i]->x, 2)
				+ pow(game->player->pos->y - game->object->objects[i]->y, 2));
	}
	ft_sort_sprite(game->object);
	i = -1;
	game->object->h_div = 1;
	game->object->v_div = 1;
	game->object->v_offset = 0;
	while (++i < game->object->nb_obj)
	{
		ft_prepare_sprite(game, game->object, &i);
		if (game->object->end_x < 0)
			game->object->end_x = 0;
		ft_draw_sprite(game, game->object, i);
	}
}

void	ft_render(t_game *game)
{
	t_render	*render;

	render = ft_init_render();
	if (!render)
		return ;
	ft_move(game);

	ft_floor(game, render);

	while (render->x < screenWidth)
	{
		render->x_offset = 0;
		render->y_offset = 0;
		ft_prepare_ray(game, render->x);
		ft_dda(game->ray);
		ft_wall_hit(game->ray, render, game);
		ft_wall_proj(game->ray, render, game);


		// ft_draw_sky_floor(game, render);

		game->object->zbuff[render->x] = render->perp_wall_dist;
		render->x++;
	}
	ft_sprite_cast(game);

	int size = (screenWidth / screenHeight) * (screenHeight / SPRITE_SIZE) / 3;
	ft_paint(game->assets->gun, game->img, ft_init_vector((screenWidth - (SPRITE_SIZE * size)) / 2, (screenHeight - SPRITE_SIZE * size)), size);
	ft_draw_minimap(game);

	free(render);
}

// int worldMap[mapWidth][mapHeight]=
// {
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1},
// 	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
// 	{1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
// 	{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1},
// 	{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 3, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
// 	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
// 	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
// 	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
// 	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
// 	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };
