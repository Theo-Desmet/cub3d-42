/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:15:02 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/15 10:36:49 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map(t_game *game, char *line, t_check *check, int line_cnt)
{
	if (!ft_is_valid_map_line(game, line))
	{
		free(line);
		return (ft_err_in_file(game, check, 1, line_cnt), 0);
	}
	check->spwan = ft_check_spawn(game, line, check->spwan, line_cnt);
	if (check->spwan < 0)
	{
		free(line);
		return (ft_err_in_file(game, check, 2, line_cnt), 0);
	}
	game->map->height++;
	return (1);
}

int	ft_is_valid_map_line(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] == '0' || line[i] == '1'
		|| line[i] == 'W' || line[i] == 'E'
		|| line[i] == 'S' || line[i] == 'N'
		|| line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
	{
		if (i > game->map->width)
			game->map->width = i;
		return (i + 1);
	}
	return (0);
}

int	ft_check_spawn(t_game *game, char *line, int spawn, int line_cnt)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'W' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'N')
		{
			game->player->heading = line[i];
			game->player->parsed_x = i;
			game->player->parsed_y = line_cnt;
			if (!spawn)
				spawn++;
			else if (spawn)
				return (-1);
		}
		i++;
	}
	return (spawn);
}

t_check	*ft_init_check(t_check *check)
{
	check->east = 0;
	check->weast = 0;
	check->north = 0;
	check->south = 0;
	check->floor = 0;
	check->ceiling = 0;
	check->spwan = 0;
	return (check);
}

int	ft_check_file(t_game *game, int fd, t_check *check)
{
	char	*line;
	int		ishead;
	int		line_cnt;
	int		len_header;

	check = ft_init_check(check);
	ishead = 1;
	line_cnt = 0;
	len_header = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_cnt++;
		if (ishead && !ft_check_is_head(line))
			ishead = ft_check_valid_head(game, check);
		if (ishead && !ft_check_map_head(game, line, check))
			return (free(line),
				ft_err_in_file(game, check, 0, line_cnt), 0);
		if (ishead)
			len_header++;
		if (!ishead && !ft_check_map(game, line, check, line_cnt - len_header - 1))
			return (0);
		free(line);
	}
	if (!check->spwan)
		return (ft_err_in_file(game, check, 3, 0), 0);
	return (1);
}
