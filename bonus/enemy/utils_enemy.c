/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:23:22 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/14 15:15:08 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_reset_path(t_enemy *enemy)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		enemy->path[i]->x = 0;
		enemy->path[i]->y = 0;
		i++;
	}
}

int	ft_signs(int nb)
{
	if (nb >= 0)
		return (1);
	return (-1);
}

void	ft_next_path(t_vector **path, int mov, int i, int dir)
{
	if (dir == 1)
	{
		path[i + 1]->y = path[i]->y;
		path[i + 1]->x = path[i]->x + mov;
	}
	else if (dir == 2)
	{
		path[i + 1]->x = path[i]->x;
		path[i + 1]->y = path[i]->y + mov;
	}
	else if (dir == 3)
	{
		path[i + 1]->x = path[i]->x;
		path[i + 1]->y = path[i]->y - mov;
	}
	else if (dir == 4)
	{
		path[i + 1]->y = path[i]->y;
		path[i + 1]->x = path[i]->x - mov;
	}
	else
	{
		path[i + 1]->x = path[i]->x;
		path[i + 1]->y = path[i]->y;
	}
}

void	ft_path_prev(t_vector **path, int *prev_x, int *prev_y, int i)
{
	if (i > 0)
	{
		*prev_x = path[i - 1]->x;
		*prev_y = path[i - 1]->y;
	}
	else
	{
		*prev_x = path[i]->x;
		*prev_y = path[i]->y;
	}
}

int	ft_valide_path(int **map, int y, int x)
{
	if (map[y][x] == 0 || map[y][x] == 4)
		return (1);
	return (0);
}
