/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:17:41 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/08 15:21:02 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_border(t_data *data, int **map)
{
	int	x;
	int	y;

	x = 1;
	if (!ft_is_line_bordere(data, map[0]))
		return (printf("ERROR: l.1"), 0);
	while (x < data->map->height - 1)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (map[x][y] != 1 && map[x][y] != -1)
				if (!ft_check_is_a_border(data, map, x, y))
					return (printf("ERROR: l.%d c%d", x, y), 0);
			y++;
		}
		x++;
	}
	if (!ft_is_line_bordere(data, map[data->map->height - 1]))
		return (printf("ERROR: l.1"), 0);
	return (1);
}

int	ft_check_is_a_border(t_data *data, int **map, int x, int y)
{
	if (y != 0 && map[x - 1][y - 1] == -1)
		return (0);
	if (map[x - 1][y] == -1)
		return (0);
	if (y < data->map->height && map[x - 1][y + 1] == -1)
		return (0);
	if (y != 0 && map[x][y - 1] == -1)
		return (0);
	if (y < data->map->height && map[x][y + 1] == -1)
		return (0);
	if (y != 0 && map[x + 1][y - 1] == -1)
		return (0);
	if (map[x + 1][y] == -1)
		return (0);
	if (y < data->map->height && map[x + 1][y + 1] == -1)
		return (0);
	return (1);
}

int	ft_is_line_bordere(t_data *data, int *line)
{
	int	i;

	i = 0;
	while (i < data->map->width)
	{
		while (i <= data->map->width && line[i] == -1)
			i++;
		while (i <= data->map->width && line[i] == 1)
			i++;
		if (i == data->map->width)
			return (1);
		if (line[i] != 1 && line[i] != -1)
			return (0);
	}
	return (1);
}
