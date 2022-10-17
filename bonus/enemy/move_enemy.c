/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:18:28 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/14 15:15:51 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_ftoi(float f)
{
	f = f * 1000;
	return ((int)f);
}

int	ft_update_path(t_enemy *enemy, t_map *map, int x, int y)
{
	if (map->map[y][x] == 7)
		map->map[y][x] = 0;
	enemy->i_path++;
	if (enemy->i_path == 9 || !enemy->path[enemy->i_path])
		return (0);
	x = ft_ftoi(enemy->path[enemy->i_path]->x);
	y = ft_ftoi(enemy->path[enemy->i_path]->y);
	if (map->map[y / 1000][x / 1000] == 0)
		map->map[y / 1000][x / 1000] = 7;
	return (1);
}

void	ft_move_enemy(t_enemy *enemy, t_map *map)
{
	int	path_x;
	int	path_y;
	int	act_x;
	int	act_y;

	if (enemy->i_path == -1)
		return ;
	path_x = ft_ftoi(enemy->path[enemy->i_path]->x);
	path_y = ft_ftoi(enemy->path[enemy->i_path]->y);
	act_x = ft_ftoi(enemy->act->x);
	act_y = ft_ftoi(enemy->act->y);
	if ((path_x == act_x && path_y == act_y)
		&& (ft_update_path(enemy, map, path_x / 1000, path_y / 1000)))
		return ;
	else if (path_x > act_x && path_y == act_y)
		enemy->act->x += 0.0625 / 2;
	else if (path_x < act_x && path_y == act_y)
		enemy->act->x -= 0.0625 / 2;
	else if (path_y > act_y && path_x == act_x)
		enemy->act->y += 0.0625 / 2;
	else if (path_y < act_y && path_x == act_x)
		enemy->act->y -= 0.0625 / 2;
}
