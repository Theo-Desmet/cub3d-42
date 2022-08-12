/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:21:01 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/12 15:22:04 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	*ft_fill_line(t_game *game, char *line, int *map)
{
	int	y;

	y = 0;
	while (y < game->map->width)
	{
		if (!line[y] || line[y] == '\n')
			while (y < game->map->width)
				map[y++] = -1;
		else if (line[y] == ' ')
			map[y] = -1;
		else if (line[y] == 'W' || line[y] == 'E'
			|| line[y] == 'N' || line[y] == 'S')
			map[y] = line[y];
		else
			map[y] = line[y] - '0';
		y++;
	}
	return (map);
}

int	**ft_fill_map(t_game *game, int **map, char *line, int fd)
{
	int	x;

	x = 0;
	while (x < game->map->height)
	{
		map[x] = malloc(sizeof(int) * game->map->width);
		if (!map[x])
			return (ft_err_copy_map(game, x), NULL);
		map[x] = ft_fill_line(game, line, map[x]);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		x++;
	}
	return (map);
}

int	ft_copy_map(t_game *game, int **map, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (0);
	line = get_next_line(fd);
	while (ft_check_is_head(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	map = ft_fill_map(game, map, line, fd);
	if (!map)
		return (0);
	return (1);
}
