/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:17:41 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/16 10:34:22 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_border(t_game *game, int **map)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map->height)
	{
		y = 0;
		while (y < game->map->width)
		{
			if (map[x][y] != 1 && map[x][y] != -1)
				if (!ft_check_is_a_border(game, map, x, y))
					return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	ft_check_is_a_border(t_game *game, int **map, int x, int y)
{
	if (y != 0 && x != 0 && map[x - 1][y - 1] == -1)
		return (ft_err_bordere(x - 1, y - 1), 0);
	if (x != 0 && map[x - 1][y] == -1)
		return (ft_err_bordere(x - 1, y), 0);
	if (y < game->map->width && x != 0 && map[x - 1][y + 1] == -1)
		return (ft_err_bordere(x - 1, y + 1), 0);
	if (y != 0 && map[x][y - 1] == -1)
		return (ft_err_bordere(x, y - 1), 0);
	if (y < game->map->width && map[x][y + 1] == -1)
		return (ft_err_bordere(x, y + 1), 0);
	if (x < game->map->height && y != 0 && map[x + 1][y - 1] == -1)
		return (ft_err_bordere(x + 1, y - 1), 0);
	if (x < game->map->height && map[x + 1][y] == -1)
		return (ft_err_bordere(x + 1, y), 0);
	if (y < game->map->width
		&& x < game->map->height && map[x + 1][y + 1] == -1)
		return (ft_err_bordere(x + 1, y + 1), 0);
	return (1);
}
