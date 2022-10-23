/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:17:41 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/23 22:34:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_wall_char(t_game *game, int y, int x)
{
	int	**map;

	if (x == 0 || y == 0 || x == game->map->width - 1
		|| y == game->map->height - 1)
		return (8);
	map = game->map->map;
	if (map[y][x + 1] == -1 || map[y + 1][x + 1] == -1 || map[y + 1][x] == -1
		|| map[y + 1][x - 1] == -1 || map[y][x - 1] == -1
			|| map[y - 1][x - 1] == -1 || map[y - 1][x] == -1
				|| map[y - 1][x + 1] == -1)
		return (8);
	return (1);
}

int	ft_check_border(t_game *game, int **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (map[y][x] != 1 && map[y][x] != -1)
				if (!ft_check_is_a_border(game, map, y, x))
					return (0);
			if (map[y][x] == 1)
				map[y][x] = ft_get_wall_char(game, y, x);
			x++;
		}
		y++;
	}
	return (1);
}

int	ft_check_is_a_border(t_game *game, int **map, int y, int x)
{
	if (y == game->map->height - 1 || x == game->map->width - 1 || !y || !x)
		return (ft_err_bordere(y, x), 0);
	if (y != 0 && x != 0 && map[y - 1][x - 1] == -1)
		return (ft_err_bordere(y - 1, x - 1), 0);
	if (y != 0 && map[y - 1][x] == -1)
		return (ft_err_bordere(y - 1, x), 0);
	if (x < game->map->width && y != 0 && map[y - 1][x + 1] == -1)
		return (ft_err_bordere(y - 1, x + 1), 0);
	if (x != 0 && map[y][x - 1] == -1)
		return (ft_err_bordere(y, x - 1), 0);
	if (x < game->map->width && map[y][x + 1] == -1)
		return (ft_err_bordere(y, x + 1), 0);
	if (y < game->map->height && x != 0 && map[y + 1][x - 1] == -1)
		return (ft_err_bordere(y + 1, x - 1), 0);
	if (y < game->map->height && map[y + 1][x] == -1)
		return (ft_err_bordere(y + 1, x), 0);
	if (y < game->map->height
		&& x < game->map->width && map[y + 1][x + 1] == -1)
		return (ft_err_bordere(y + 1, x + 1), 0);
	return (1);
}
