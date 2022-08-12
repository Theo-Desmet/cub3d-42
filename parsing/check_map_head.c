/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_head.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:42:10 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/10 11:50:28 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_head(t_data *data, char *line, t_check *check)
{
	if (*line == '\n')
		return (2);
	else if (ft_check_valid_path(line, "EA ") && !check->east)
		check->east = 1;
	else if (ft_check_valid_path(line, "WE ") && !check->weast)
		check->weast = 1;
	else if (ft_check_valid_path(line, "NO ") && !check->north)
		check->north = 1;
	else if (ft_check_valid_path(line, "SO ") && !check->south)
		check->south = 1;
	else if (ft_check_is_rgb(line, "F ") && !check->floor)
	{
		data->assets->floor = ft_check_is_rgb(line, "F ");
		check->floor = 1;
	}
	else if (ft_check_is_rgb(line, "C ") && !check->ceiling)
	{
		data->assets->ceiling = ft_check_is_rgb(line, "C ");
		check->ceiling = 1;
	}
	else
		return (0);
	return (1);
}

int	ft_check_is_head(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!ft_strncmp(&str[i], "EA ", 3)
		|| !ft_strncmp(&str[i], "WE ", 3)
		|| !ft_strncmp(&str[i], "NO ", 3)
		|| !ft_strncmp(&str[i], "SO ", 3)
		|| !ft_strncmp(&str[i], "F ", 2)
		|| !ft_strncmp(&str[i], "C ", 2)
		|| str[i] == '\n')
		return (1);
	return (0);
}

int	ft_check_valid_head(t_data *data, t_check *check)
{
	if (!check->east)
		return (ft_putstr_fd("error in file: Invalide line in head\n", 2), 1);
	if (!check->weast)
		return (ft_putstr_fd("error in file: Invalide line in head\n", 2), 1);
	if (!check->north)
		return (ft_putstr_fd("error in file: Invalide line in head\n", 2), 1);
	if (!check->south)
		return (ft_putstr_fd("error in file: Invalide line in head\n", 2), 1);
	if (!check->floor)
		return (ft_putstr_fd("error in file: Invalide line in head\n", 2), 1);
	if (!check->ceiling)
		return (ft_putstr_fd("error in file: Invalide line in head\n", 2), 1);
	return (0);
}
