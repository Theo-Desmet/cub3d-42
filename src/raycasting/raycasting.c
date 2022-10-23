/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:49:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/23 23:15:46 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_render	*ft_init_render(void)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	ft_memset(render, 0, sizeof(t_render));
	return (render);
}

void	ft_render(t_game *game)
{
	t_render	*render;

	render = ft_init_render();
	if (!render)
		return ;
	ft_move(game);
	while (render->x < S_WIDTH)
	{
		render->x_offset = 0;
		render->y_offset = 0;
		ft_prepare_ray(game, render->x);
		ft_dda(game->ray);
		ft_wall_hit(game->ray, game);
		ft_wall_proj(game->ray, render, game);
		ft_draw_sky_floor(game, render);
		render->x++;
	}
	free(render);
}
