/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:17:41 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/12 11:57:06 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_border(t_data *data, int **map)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->map->height)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (map[x][y] != 1 && map[x][y] != -1)
				if (!ft_check_is_a_border(data, map, x, y))
					return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	ft_check_is_a_border(t_data *data, int **map, int x, int y)
{
	if (y != 0 && x != 0 && map[x - 1][y - 1] == -1)
		return (ft_err_bordere(x - 1, y - 1), 0);
	if (x != 0 && map[x - 1][y] == -1)
		return (ft_err_bordere(x - 1, y), 0);
	if (y < data->map->width && x != 0 && map[x - 1][y + 1] == -1)
		return (ft_err_bordere(x - 1, y + 1), 0);
	if (y != 0 && map[x][y - 1] == -1)
		return (ft_err_bordere(x, y - 1), 0);
	if (y < data->map->width && map[x][y + 1] == -1)
		return (ft_err_bordere(x, y + 1), 0);
	if (x < data->map->height && y != 0 && map[x + 1][y - 1] == -1)
		return (ft_err_bordere(x + 1, y - 1), 0);
	if (x < data->map->height && map[x + 1][y] == -1)
		return (ft_err_bordere(x + 1, y), 0);
	if (y < data->map->width
		&& x < data->map->height && map[x + 1][y + 1] == -1)
		return (ft_err_bordere(x + 1, y + 1), 0);
	return (1);
}
