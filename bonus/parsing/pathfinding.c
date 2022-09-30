/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:50:28 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/18 14:57:10 by tdesmet          ###   ########.fr       */
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
		path[i + 1]->y = path[i]->y + mov;
		path[i + 1]->x = path[i]->x;
	}
	else if (dir == 2)
	{
		path[i + 1]->x = path[i]->x + mov;
		path[i + 1]->y = path[i]->y;
	}
	else if (dir == 3)
	{
		path[i + 1]->x = path[i]->x - mov;
		path[i + 1]->y = path[i]->y;
	}
	else if (dir == 4)
	{
		path[i + 1]->y = path[i]->y - mov;
		path[i + 1]->x = path[i]->x;
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

void	ft_hori_mov(t_vector **path, int **map, int i, t_vector *mov)
{
	int	x_prev;
	int	y_prev;

	mov->x = ft_signs(mov->x);
	mov->y = ft_signs(mov->y);
	ft_path_prev(path, &x_prev, &y_prev, i);
	if (map[(int)path[i]->x][(int)(path[i]->y + mov->y)] != 1
		&& y_prev != path[i]->y + mov->y)
		ft_next_path(path, mov->y, i, 1);
	else if (map[(int)(path[i]->x + mov->x)][(int)path[i]->y] != 1
		&& x_prev != path[i]->x + mov->x)
		ft_next_path(path, mov->x, i, 2);
	else if (map[(int)(path[i]->x - mov->x)][(int)path[i]->y] != 1
		&& x_prev != path[i]->x - mov->x)
		ft_next_path(path, mov->x, i, 3);
	else if (map[(int)path[i]->x][(int)(path[i]->y - mov->y * -1)] != 0)
		ft_next_path(path, mov->y, i, 4);
	else
		ft_next_path(path, mov->y, i, 0);
}

void	ft_vert_mov(t_vector **path, int **map, int i, t_vector *mov)
{
	int	x_prev;
	int	y_prev;

	mov->x = ft_signs(mov->x);
	mov->y = ft_signs(mov->y);
	ft_path_prev(path, &x_prev, &y_prev, i);
	if (map[(int)(path[i]->x + mov->x)][(int)path[i]->y] != 1
		&& x_prev != path[i]->x + mov->x)
		ft_next_path(path, mov->x, i, 2);
	else if (map[(int)path[i]->x][(int)(path[i]->y + mov->y)] != 1
		&& y_prev != path[i]->y + mov->y)
		ft_next_path(path, mov->y, i, 1);
	else if (map[(int)path[i]->x][(int)(path[i]->y - mov->y)] != 1
		&& y_prev != path[i]->y - mov->y)
		ft_next_path(path, mov->y, i, 4);
	else if (map[(int)(path[i]->x - mov->x)][(int)path[i]->y] != 1)
		ft_next_path(path, mov->x, i, 3);
	else
		ft_next_path(path, mov->y, i, 0);
}

void	ft_search_path(t_enemy *enemy, int **map, int i)
{
	t_vector	*delta;

	delta = malloc(sizeof(t_vector));
	delta->x = enemy->dest->x - enemy->path[i]->x;
	delta->y = enemy->dest->y - enemy->path[i]->y;
	if (delta->x * delta->x >= delta->y * delta->y)
		ft_vert_mov(enemy->path, map, i, delta);
	else
		ft_hori_mov(enemy->path, map, i, delta);
}

void	ft_pathfinding(t_enemy *enemy, t_map *map)
{
	int	i;

	ft_random_place(enemy, map);
	i = 0;
	while (i < 10)
		enemy->path[i++] = malloc(sizeof(t_vector));
	i = 0;
	enemy->path[0]->x = enemy->act->x;
	enemy->path[0]->y = enemy->act->y;
	while (i < 9 && !(enemy->path[i]->x == enemy->dest->x
			&& enemy->path[i]->y == enemy->dest->y))
	{
		ft_search_path(enemy, map->map, i);
		i++;
//		printf("%d  %d\n", (int)enemy->path[i]->x, (int)enemy->path[i]->y);
		if (enemy->path[i]->x == enemy->dest->x
			&& enemy->path[i]->y == enemy->dest->y)
			break ;
	}
}