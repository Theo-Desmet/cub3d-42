/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_head.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:42:10 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/21 14:24:22 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_head(t_game *game, char *line, t_check *check)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]) && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (2);
	else if (ft_check_valid_path(game, line, "EA") && !check->east)
		check->east = 1;
	else if (ft_check_valid_path(game, line, "WE") && !check->weast)
		check->weast = 1;
	else if (ft_check_valid_path(game, line, "NO") && !check->north)
		check->north = 1;
	else if (ft_check_valid_path(game, line, "SO") && !check->south)
		check->south = 1;
	else if (!check->floor && ft_check_is_rgb(line, 'F', &check->floor))
		game->floor_color = ft_check_is_rgb(line, 'F', &check->floor);
	else if (!check->ceiling && ft_check_is_rgb(line, 'C', &check->ceiling))
		game->ceiling_color = ft_check_is_rgb(line, 'C', &check->ceiling);
	else
		return (0);
	return (1);
}

int	ft_check_is_head(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) && str[i] != '\n')
		i++;
	if (!ft_strncmp(&str[i], "EA", 2)
		|| !ft_strncmp(&str[i], "WE", 2)
		|| !ft_strncmp(&str[i], "NO", 2)
		|| !ft_strncmp(&str[i], "SO", 2)
		|| !ft_strncmp(&str[i], "F", 1)
		|| !ft_strncmp(&str[i], "C", 1)
		|| str[i] == '\n')
		return (1);
	return (0);
}

int	ft_check_valid_head(t_game *game, t_check *check)
{
	if (!check->east || !check->weast || !check->north || !check->south
		|| !check->floor || !check->ceiling)
		return (ft_putstr_fd(INV_HDR, 2), 1);
	return (0);
}
