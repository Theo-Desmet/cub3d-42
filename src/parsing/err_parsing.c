/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:03:06 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/21 16:08:45 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_err_file_name(t_game *game, int argc, int error)
{
	if (argc < 2)
		ft_putstr_fd(NO_FILE, 2);
	if (argc > 2)
		ft_putstr_fd(TOO_MANY_FILES, 2);
}

void	ft_get_error_msg(int error)
{
	if (error == 0)
		ft_putstr_fd(INV_SYN, 2);
	else if (error == 1)
		ft_putstr_fd(INV_CHAR, 2);
	else if (error == 2)
		ft_putstr_fd(MULTI_SPAWN, 2);
	else
		ft_putstr_fd(NO_SPAWN, 2);
}

void	ft_err_in_file(t_game *game, int error, int line)
{
	if (error >= 0 && error <= 2)
	{
		ft_putstr_fd("Error\nIn map at line ", 2);
		ft_putnbr_fd(line, 2);
		ft_get_error_msg(error);
	}
	else
		ft_get_error_msg(error);
	if (error == 2 || error == 3)
	{
		game->map->width = 0;
		game->map->height = 0;
	}
}

void	ft_err_copy_map(t_game *game)
{
	game->map->width = 0;
	game->map->height = 0;
	ft_putstr_fd(COPY_ERROR, 2);
}

void	ft_err_bordere(int x, int y)
{
	ft_putstr_fd("Error\nIn map at line ", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(" column ", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(": the map is open\n", 2);
}
