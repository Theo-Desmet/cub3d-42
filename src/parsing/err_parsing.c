/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:03:06 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/20 16:43:13 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_err_file_name(t_game *game, int argc, int error)
{
	if (argc < 2)
		ft_putstr_fd(game->error_msg[NO_FILE], 2);
	if (argc > 2)
		ft_putstr_fd(game->error_msg[TOO_MANY_FILE], 2);
	if (error > 0)
		ft_putstr_fd(game->error_msg[error], 2);
}

char	*ft_get_error_msg(t_game *game, int error)
{
	if (error == 0)
		return (game->error_msg[INVALID_SYNTAX]);
	if (error == 1)
		return (game->error_msg[INVALID_CHAR]);
	if (error == 2)
		return (game->error_msg[MULTI_SPAWN]);
	return (game->error_msg[NO_SPAWN]);
}

void	ft_err_in_file(t_game *game, int error, int line)
{
	if (error >= 0 && error <= 2)
	{
		ft_putstr_fd("error in map: line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(ft_get_error_msg(game, error), 2);
	}
	else
		ft_putstr_fd(ft_get_error_msg(game, error), 2);
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
	ft_putstr_fd(game->error_msg[COPY_ERROR], 2);
}

void	ft_err_bordere(int x, int y)
{
	ft_putstr_fd("err in map: line ", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(" columnum ", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(": the map is open\n", 2);
}
