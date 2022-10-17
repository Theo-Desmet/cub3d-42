/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:40:50 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/13 16:48:01 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_is_valide_place(t_map *map, int x, int y)
{
	if (x >= map->width || x < 0 || y >= map->height || y < 0)
		return (0);
	if (map->map[y][x] == 0)
		return (1);
	return (0);
}

void	ft_random_mod(int *x, int *y)
{
	*x = rand();
	*y = rand();
	*x %= 5;
	*y %= 5;
}

void	ft_spawn_enemy(t_game *game)
{
	int	x;
	int	y;
	int	i;

	if (!game->enemy || game->map->height < 10 || game->map->width < 10)
		game->enemy_spw = false;
	i = 0;
	while (i++ < 1000)
	{
		x = rand();
		y = rand();
		x %= (game->map->width - 1);
		y %= (game->map->height - 1);
		if (ft_is_valide_place(game->map, x, y))
		{
			game->enemy_spw = true;
			game->enemy->act->x = x;
			game->enemy->act->y = y;
			game->enemy->dest->x = x;
			game->enemy->dest->y = y;
			return ;
		}
	}
	game->enemy_spw = false;
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
		ft_random_mod(&x, &y);
		rng = rand() % 2;
		if (rng == 1)
			x *= -1;
		rng = rand() % 2;
		if (rng == 1)
			y *= -1;
		if (ft_is_valide_place(map, enemy->act->x + x, enemy->act->y + y))
		{
			enemy->dest->x = enemy->act->x + x;
			enemy->dest->y = enemy->act->y + y;
			return ;
		}
		valide++;
	}
}
