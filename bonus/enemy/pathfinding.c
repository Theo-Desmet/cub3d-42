/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:50:28 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/14 15:05:12 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_hori_mov(t_vector **path, int **map, int i, t_vector *mov)
{
	int	x_prev;
	int	y_prev;

	mov->x = ft_signs(mov->x);
	mov->y = ft_signs(mov->y);
	ft_path_prev(path, &x_prev, &y_prev, i);
	if (ft_valide_path(map, (int)path[i]->y, (int)(path[i]->x + mov->x))
		&& x_prev != path[i]->x + mov->x)
		ft_next_path(path, mov->x, i, 1);
	else if (ft_valide_path(map, (int)(path[i]->y + mov->y), (int)path[i]->x)
		&& y_prev != path[i]->y + mov->y)
		ft_next_path(path, mov->y, i, 2);
	else if (ft_valide_path(map, (int)(path[i]->y - mov->y), (int)path[i]->x)
		&& y_prev != path[i]->y - mov->y)
		ft_next_path(path, mov->y, i, 3);
	else if (ft_valide_path(map, (int)path[i]->y, (int)(path[i]->x - mov->x)))
		ft_next_path(path, mov->x, i, 4);
	else
		ft_next_path(path, 0, i, 0);
}

void	ft_vert_mov(t_vector **path, int **map, int i, t_vector *mov)
{
	int	x_prev;
	int	y_prev;

	mov->x = ft_signs(mov->x);
	mov->y = ft_signs(mov->y);
	ft_path_prev(path, &x_prev, &y_prev, i);
	if (ft_valide_path(map, (int)(path[i]->y + mov->y), (int)path[i]->x)
		&& y_prev != path[i]->y + mov->y)
		ft_next_path(path, mov->y, i, 2);
	else if (ft_valide_path(map, (int)path[i]->y, (int)(path[i]->x + mov->x))
		&& x_prev != path[i]->x + mov->x)
		ft_next_path(path, mov->x, i, 1);
	else if (ft_valide_path(map, (int)path[i]->y, (int)(path[i]->x - mov->x))
		&& x_prev != path[i]->x - mov->x)
		ft_next_path(path, mov->x, i, 4);
	else if (ft_valide_path(map, (int)(path[i]->y - mov->y), (int)path[i]->x))
		ft_next_path(path, mov->y, i, 3);
	else
		ft_next_path(path, 0, i, 0);
}

void	ft_search_path(t_enemy *enemy, int **map, int i)
{
	t_vector	delta;

	delta = (t_vector)
	{enemy->dest->x - enemy->path[i]->x, enemy->dest->y - enemy->path[i]->y};
	if (delta.x * delta.x >= delta.y * delta.y)
		ft_hori_mov(enemy->path, map, i, &delta);
	else
		ft_vert_mov(enemy->path, map, i, &delta);
}

void	ft_pathfinding(t_game *game, t_enemy *enemy, t_map *map)
{
	int	i;

	if (game->enemy_spw == false)
		return ;
	ft_move_enemy(enemy, map);
	if (enemy->i_path == 10
		|| (ft_ftoi(enemy->act->x) == ft_ftoi(enemy->dest->x)
			&& (ft_ftoi(enemy->act->y) == ft_ftoi(enemy->dest->y)
				|| !enemy->path[enemy->i_path])))
	{
		i = 0;
		enemy->i_path = 0;
		ft_random_place(enemy, map);
		ft_reset_path(enemy);
		enemy->path[0]->x = enemy->act->x;
		enemy->path[0]->y = enemy->act->y;
		while (i < 9 && !(enemy->path[i]->x == enemy->dest->x
				&& enemy->path[i]->y == enemy->dest->y))
		{
			ft_search_path(enemy, map->map, i);
			i++;
		}
	}
}
