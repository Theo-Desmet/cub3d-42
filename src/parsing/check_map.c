/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:15:02 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/17 11:42:31 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map(t_game *game, char *line, t_check *check, int line_cnt)
{
	if (!ft_is_valid_map_line(game, line))
	{
		free(line);
		return (ft_err_in_file(game, 1, line_cnt), 0);
	}
	check->spawn = ft_check_spawn(game, line, check->spawn, line_cnt);
	if (check->spawn < 0)
	{
		free(line);
		return (ft_err_in_file(game, 2, line_cnt), 0);
	}
	game->map->height++;
	return (1);
}

int	ft_is_valid_map_line(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (ft_strchr("01EWSN ", line[i]))
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
	check->spawn = 0;
	return (check);
}

int	ft_check_file(t_game *game, int fd, t_check *check)
{
	check = ft_init_check(check);
	check->is_head = true;
	check->line_cnt = 0;
	check->len_hdr = 0;
	while (1)
	{
		check->line = get_next_line(fd);
		if (!check->line)
			break ;
		check->line_cnt++;
		if (check->is_head && !ft_check_is_head(check->line))
			check->is_head = ft_check_valid_head(game, check);
		if (check->is_head && !ft_check_map_head(game, check->line, check))
			return (free(check->line),
				ft_err_in_file(game, 0, check->line_cnt), 0);
		if (check->is_head)
			check->len_hdr++;
		if (!check->is_head && !ft_check_map(game, check->line, check,
				check->line_cnt - check->len_hdr - 1))
			return (0);
		free(check->line);
	}
	if (!check->spawn)
		return (ft_err_in_file(game, 3, 0), 0);
	return (1);
}
