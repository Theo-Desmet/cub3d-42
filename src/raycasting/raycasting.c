/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:49:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/11 22:11:35 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

int	ft_free_all(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img->mlx_img);
	free(game->img);
	if (game->assets)
		ft_free_assets(game->assets, game->mlx);
	if (game->player)
		ft_free_player(game->player);
	if (game->ray)
		ft_free_ray(game->ray);
	if (game->plane)
		free(game->plane);
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

void	ft_render(t_game *game)
{
	t_render	*render;

	render = ft_init_render();
	if (!render)
		return ;
	ft_move(game);
	while (render->x < screenWidth)
	{
		render->x_offset = 0;
		render->y_offset = 0;
		ft_prepare_ray(game, render->x);
		ft_dda(game->ray);
		ft_wall_hit(game->ray, render, game);
		ft_wall_proj(game->ray, render, game);
		ft_draw_sky_floor(game, render);
		render->x++;
	}
	free(render);
}
