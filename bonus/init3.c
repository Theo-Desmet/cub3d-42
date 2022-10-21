/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:55:41 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/21 16:22:01 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_door	**ft_get_doors(t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	game->nb_doors = 0;
	ft_alloc_doors(game);
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->map[y][x] == 3)
			{
				game->doors[i] = ft_init_door(x, y);
				if (!game->doors[i])
					return (ft_free_tab((void **)game->doors), NULL);
				i++;
			}
		}
	}
	return (game->doors);
}

void	ft_update_heading(t_game *game, double x, double y)
{
	game->player->dir->x = x;
	game->player->dir->y = y;
	game->plane->x = -y * ((FOV / 2 * M_PI) / 180);
	game->plane->y = x * ((FOV / 2 * M_PI) / 180);
}

void	ft_update_player(t_game *game)
{
	game->player->pos->x = (double)game->player->parsed_x + 0.5;
	game->player->pos->y = (double)game->player->parsed_y + 0.5;
	if (game->player->heading == 'W')
		ft_update_heading(game, -1.0, 0.0);
	else if (game->player->heading == 'E')
		ft_update_heading(game, 1.0, 0.0);
	else if (game->player->heading == 'S')
		ft_update_heading(game, 0.0, 1.0);
	else
		ft_update_heading(game, 0.0, -1.0);
}

t_game	*ft_alloc_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_memset((void *)game, 0, sizeof(t_game));
	return (game);
}
