/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:15:02 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/08 16:09:40 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map(t_data *data, char *line, t_check *check)
{
	if (!ft_is_valid_map_line(data, line))
	{
		free(line);
		return (0);
	}
	check->spwan = ft_check_spawn(line, check->spwan);
	if (check->spwan < 0)
	{
		free(line);
		return (0);
	}
	data->map->height++;
	return (1);
}

int	ft_is_valid_map_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1' && line[i] != '\n')
		return (0);
	while (line[i] == '0' || line[i] == '1'
		|| line[i] == 'W' || line[i] == 'E'
		|| line[i] == 'S' || line[i] == 'N')
		i++;
	if (!line[i] || line[i] == '\n')
	{
		if (i > data->map->width)
			data->map->width = i;
		return (i + 1);
	}
	return (0);
}

int	ft_check_spawn(char *line, int spawn)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'W' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'N')
		{
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

int	ft_check_file(t_data *data, int fd, t_check *check)
{
	char	*line;
	int		ishead;

	check = ft_init_check(check);
	ishead = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ishead && !ft_check_is_head(line))
			ishead = 0;
		if (ishead && !ft_check_map_head(data, line, check))
			return (0);//add msg error
		if (!ishead && !ft_check_map(data, line, check))
			return (0);//add msg error
		free(line);
	}
	if (!check->spwan)
		return (0);
	free(check);
	return (1);
}
