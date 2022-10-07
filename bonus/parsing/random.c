/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:40:50 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/07 09:43:01 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_is_valide_place(t_enemy *enemy, t_map *map, int x, int y)
{
	if (x >= map->height || x < 0 || y >= map->width || y < 0)
		return (0);
	if (map->map[x][y] == 0)
		return (1);
	return (0);
}

void	ft_mod_size(t_map *map, int *mod_x, int *mod_y)
{
	if (map->height < 7)
		*mod_x = map->height - 2;
	else
		*mod_x = 5;
	if (map->width < 7)
		*mod_y = map->width - 2;
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

void	ft_spawn_enemy(t_game *game)
{
	int	x;
	int	y;
	int	i;

	if (game->map->height < 10 || game->map->width < 10)
		game->enemy_spw = false;
	i = 0;
	while (i++ < 100)
	{
		x = rand();
		y = rand();
		x %= (game->map->height - 1);
		y %= (game->map->width - 1);
		if (ft_is_valide_place(game->enemy, game->map, x, y)
			&& (x > game->player->pos->x + 5 || x < game->player->pos->x - 5)
			&& (y > game->player->pos->y + 5 || y < game->player->pos->y - 5))
		{
			game->enemy_spw = true;
			game->enemy->act->x = x;
			game->enemy->act->y = y;
			//game->map->map[(int)game->enemy->act->x][(int)game->enemy->act->y] = 7;
			game->enemy->dest->x = x;
			game->enemy->dest->y = y;
			printf("init %f %f\n", game->enemy->act->y, game->enemy->act->x);
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
		ft_random_mod(map, &x, &y);
		rng = rand() % 2;
		if (rng == 1)
			x *= -1;
		rng = rand() % 2;
		if (rng == 1)
			y *= -1;
		if (ft_is_valide_place(enemy, map, enemy->act->x + x, enemy->act->y + y))
		{
			enemy->dest->x = enemy->act->x + x;
			enemy->dest->y = enemy->act->y + y;
			return ;
		}
		valide++;
	}
}
