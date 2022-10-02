/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:40 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/01 14:47:04 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_sky_floor(t_game *game, t_render *render)
{
	render->y = render->end;
	while (render->y < S_HEIGHT)
	{
		ft_put_pixel(game->img, render->x, render->y,
			game->floor_color);
		ft_put_pixel(game->img, render->x, S_HEIGHT - render->y - 1,
			game->ceiling_color);
		render->y++;
	}
}
