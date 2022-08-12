/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:50:28 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/12 17:17:20 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*ft_search_path(int **map, int **path, int i, int x_end, int y_end)
{
	int	delta_x;
	int	delta_y;

	delta_x = path[i][0] - x_end;
	delta_y = path[i][1] - y_end;
	if (delta_x == delta_y && i > 0)
	{
		delta_x = path[i][0] - x_end;
		delta_y = path[i][1] - y_end;
	}
	if (delta_x * delta_x > delta_y * delta_y)
	{
		if (delta_x > 0)
			//deplacement
		else
			//deplacement
	}
	else
	{
		if (delta_y > 0)
			//deplacement
		else
			//deplacement
	}
}

int	ft_hori_mov(int **map, int **path, int i, int mov_x, int mov_y)
{
	int	x_prev;
	int	y_prev;

	if (i > 0)
	{
		x_prev = path[i - 1][0];
		y_prev = path[i - 1][1];
	}
	else
	{
		x_prev = path[i][0];
		y_prev = path[i][1];
	}
	if (map[path[i][0]][path[i][1] + mov_y] != 1 && y_prev != path[i][1] + mov_y)
		//move;
	else if (map[path[i][0] + mov_x][path[i][1]] != 1 && x_prev != path[i][0] + mov_x)
		//move;
	else if (map[path[i][0] + mov_x * -1][path[i][1]] != 1 && x_prev != path[i][0] + mov_x * -1)
		//move;
	else if (map[path[i][0]][path[i][1] + mov_y * -1] != 1 && y_prev != path[i][1] + mov_y * -1)
		//move;
	return (NULL);
}

int	ft_vert_mov(int **map, int **path, int i, int mov_x, int mov_y)
{
	int	x_prev;
	int	y_prev;

	if (i > 0)
	{
		x_prev = path[i - 1][0];
		y_prev = path[i - 1][1];
	}
	else
	{
		x_prev = path[i][0];
		y_prev = path[i][1];
	}
	if (map[path[i][0] + mov_x][path[i][1]] != 1 && x_prev != path[i][0] + mov_x)
		//move;
	if (map[path[i][0]][path[i][1] + mov_y] != 1 && y_prev != path[i][1] + mov_y)
		//move;
	else if (map[path[i][0]][path[i][1] + mov_y * -1] != 1 && y_prev != path[i][1] + mov_y * -1)
		//move;
	else if (map[path[i][0] + mov_x * -1][path[i][1]] != 1 && x_prev != path[i][0] + mov_x * -1)
		//move;
	return (NULL);
}
void	ft_pathfinding(map **map)
{
	int pos_start_x;
	int pos_start_y;
	int pos_end_x;
	int pos_end_y;
	int i;
	int path[30][2];

	pos_start_x = 3;
	pos_start_y = 9;
	pos_end_x = 3;
	pos_end_y = 16;
	i = 0;
	path[0][0] = pos_start_x;
	path[0][1] = pos_start_y;
	while (i < 30 && path[i][0] != pos_end_x && path[i][1] != pos_end_y)
	{
		path[i + 1] = ft_search_path(map, path, i, pos_end_x, pos_end_y);
		printf("posx = %d, posy = %d", path[i][0], path[i][1]);//sdf
		i++;
	}
}
