/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:40 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/21 02:42:13 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_sky_floor(t_game *game, t_render *render)
{
	render->y = render->end;
	while (render->y < screenHeight)
	{
		ft_put_pixel(game->img, render->x, render->y,
			game->floor_color);
		ft_put_pixel(game->img, render->x, screenHeight - render->y - 1,
			game->ceiling_color);
		render->y++;
	}
}
