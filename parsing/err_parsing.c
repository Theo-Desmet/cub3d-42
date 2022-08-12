/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:03:06 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/12 11:55:09 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_data(t_data *data)
{
	mlx_destroy_display(data->mlx);
	free(data->assets);
	if (data->map->width == 0 || data->map->height == 0)
		free(data->map);
	else
		ft_free_map(data, data->map->height - 1);
	free(data->mlx);
	free(data);
}

void	ft_err_file_name(t_data *data, int argc, int error)
{
	ft_free_data(data);
	if (argc < 2)
		ft_putstr_fd("bad file: please add an file whit .cub extension\n", 2);
	if (argc > 2)
		ft_putstr_fd("bad file: too many file, please use only one\n", 2);
	if (error == 1)
		ft_putstr_fd("bad extension file: filename need .cub extension\n", 2);
	if (error == 2)
		ft_putstr_fd("bad filename: please use a valid filename\n", 2);
	if (error == 3)
		ft_putstr_fd("bad filename: file not found\n", 2);
}

void	ft_err_in_file(t_data *data, t_check *check, int error, int line)
{
	char	*line_nb;

	line_nb = ft_itoa(line);
	if (error == 0)
	{
		ft_putstr_fd("error in file: line ", 2);
		ft_putstr_fd(line_nb, 2);
		ft_putstr_fd(": use or redifine of an invalide syntax\n", 2);
	}
	if (error == 1)
	{
		ft_putstr_fd("error in file: line ", 2);
		ft_putstr_fd(line_nb, 2);
		ft_putstr_fd(": use of an invalide caratere on map\n", 2);
	}
	if (error == 2)
	{	
		ft_putstr_fd("error in file: line ", 2);
		ft_putstr_fd(line_nb, 2);
		ft_putstr_fd(": redifine of spwan, please use only one\n", 2);
		data->map->width = 0;
		data->map->height = 0;
	}
	if (error == 3)
	{
		ft_putstr_fd("error in file: no spwan in map\n", 2);
		data->map->width = 0;
		data->map->height = 0;
	}
	free(line_nb);
}

void	ft_err_copy_map(t_data *data, int nb_line)
{
	ft_free_map(data, nb_line - 1);
	data->map->width = 0;
	data->map->height = 0;
	ft_putstr_fd("error during the copy of the map, please retry\n", 2);
}

void	ft_err_bordere(int x, int y)
{
	char	*char_x;
	char	*char_y;

	char_x = ft_itoa(x + 1);
	char_y = ft_itoa(y + 1);
	ft_putstr_fd("err in map: line ", 2);
	ft_putstr_fd(char_x, 2);
	ft_putstr_fd(" columnum ", 2);
	ft_putstr_fd(char_y, 2);
	ft_putstr_fd(": the map is open\n", 2);
	free(char_x);
	free(char_y);
}
