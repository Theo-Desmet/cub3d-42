/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:50:28 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/13 11:39:53 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	if (map[y][x] == 0 || map [y][x] == 4)
		return (1);
	return (0);
}

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

	delta = (t_vector){enemy->dest->x - enemy->path[i]->x
		, enemy->dest->y - enemy->path[i]->y};
	if (delta.x * delta.x >= delta.y * delta.y)
		ft_hori_mov(enemy->path, map, i, &delta);
	else
		ft_vert_mov(enemy->path, map, i, &delta);
}

int	ft_ftoi(float f)
{
	f = f * 10;
	return ((int)f);
}

void	ft_move_enemy(t_enemy *enemy, t_map *map)
{
	int	path_x;
	int	path_y;
	int	act_x;
	int	act_y;

	if (enemy->i_path == 9 || enemy->i_path == -1 || !enemy->path[enemy->i_path])
		return ;
	path_x = ft_ftoi(enemy->path[enemy->i_path]->x);
	path_y = ft_ftoi(enemy->path[enemy->i_path]->y);
	act_x = ft_ftoi(enemy->act->x);
	act_y = ft_ftoi(enemy->act->y);
	if ((path_x == act_x && path_y == act_y))
	{
		if (map->map[path_y / 10][path_x / 10] == 7)
			map->map[path_y / 10][path_x / 10] = 0;
		enemy->i_path++;
		if (enemy->i_path == 9 || !enemy->path[enemy->i_path])
			return ;
		path_x = ft_ftoi(enemy->path[enemy->i_path]->x);
		path_y = ft_ftoi(enemy->path[enemy->i_path]->y);
		if (map->map[path_y / 10][path_x / 10] == 0)
		{
			printf("%d  %d  %d\n", map->map[path_y / 10][path_x / 10], path_y / 10, path_x / 10);
			map->map[path_y / 10][path_x / 10] = 7;
		}
	}
	else if (path_x > act_x && path_y == act_y)	
		enemy->act->x += 0.0625 / 2;
	else if (path_x < act_x && path_y == act_y)	
		enemy->act->x -= 0.0625 / 2;
	else if (path_y > act_y && path_x == act_x)
		enemy->act->y += 0.0625 / 2;
	else if (path_y < act_y && path_x == act_x)	
		enemy->act->y -= 0.0625 / 2;
}

void	ft_pathfinding(t_game *game, t_enemy *enemy, t_map *map)
{
	int	i;

	if (game->enemy_spw == false)
		return ;
	ft_move_enemy(enemy, map);
	if (enemy->i_path == 10 || (ft_ftoi(enemy->act->x) == ft_ftoi(enemy->dest->x)
		&& (ft_ftoi(enemy->act->y) == ft_ftoi(enemy->dest->y)
		|| !enemy->path[enemy->i_path])))
	{
		ft_random_place(enemy, map);
		i = 0;
			enemy->path = ft_memset(enemy->path, 0, sizeof(enemy->path));//a bouger
		while (i < 10)
			enemy->path[i++] = malloc(sizeof(t_vector));//secu
		i = 0;
		enemy->i_path = 0;
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
