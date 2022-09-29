/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:40:50 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/18 12:03:11 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_is_valide_place(t_enemy *enemy, t_map *map, int x, int y)
{
	if ((int)enemy->act->x + x >= map->height
		|| (int)enemy->act->x + x < 0
		|| (int)enemy->act->y + y >= map->width
		|| (int)enemy->act->y + y < 0)
		return (0);
	if (map->map[(int)enemy->act->x + x][(int)enemy->act->y + y] == 0)
	{
		enemy->dest->x = enemy->act->x + x;
		enemy->dest->y = enemy->act->y + y;
		return (1);
	}
	return (0);
}

void	ft_mod_size(t_map *map, int *mod_x, int *mod_y)
{
	if (map->height < 7)
		*mod_x = map->height - 2;
	else
		*mod_x = 5;
	if (map->width < 7)
		*mod_y = map->height - 2;
	else
		*mod_y = 5;
}

void	ft_random_mod(t_map *map, int *x, int *y)
{
	int	mod_x;
	int	mod_y;

	ft_mod_size(map, &mod_x, &mod_y);
	*x = rand();
	*y = rand();
	*x %= mod_x;
	*y %= mod_y;
}

int	ft_spawn_enemy(t_enemy *enemy, t_map *map)
{
	int	x;
	int	y;

	if (map->height < 10 || map->width < 10)
		return (0);
	enemy->act->x = 1;
	enemy->act->y = 1;
	return (1);
}

void	ft_random_place(t_enemy *enemy, t_map *map)
{
	int	rng;
	int	x;
	int	y;
	int	valide;

	valide = 0;
	while (valide < 10)
	{
		ft_random_mod(map, &x, &y);
		rng = rand() % 2;
		if (rng == 1)
			x *= -1;
		rng = rand() % 2;
		if (rng == 1)
			y *= -1;
		if (ft_is_valide_place(enemy, map, x, y))
			return ;
		enemy->dest->x = enemy->act->x;
		enemy->dest->y = enemy->act->y;
		valide++;
	}
}
