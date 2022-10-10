/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:10:09 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/08 12:10:36 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_sprite	*ft_create_enemy(t_game *game, t_object *obj)
{
	t_img		*enemy;
	t_sprite	*res;

	enemy = ft_init_img(game->mlx, "assets/ennemy.xpm", SP_SIZE * 5,
			SP_SIZE * 5);
	res = ft_init_sprite(game, game->enemy->act->x + 0.5,
			game->enemy->act->y + 0.5, enemy);
	res->type = ENEMY;
	res->animated = true;
	game->enemy->sprite = res;
	return (res);
}

t_enemy	*ft_init_enemy(void)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
			return (NULL);
	enemy->act = malloc(sizeof(t_vector));
	if (!enemy->act)
			return (ft_free_enemy(enemy), NULL);
	enemy->act->x = 1;//spawn a mdf
	enemy->act->y = 1;//spawn a mdf
	enemy->dest = malloc(sizeof(t_vector));
	if (!enemy->dest)
		return (ft_free_enemy(enemy), NULL);
	enemy->img_enemy = malloc(sizeof(t_img));
	if (!enemy->img_enemy)
		return (ft_free_enemy(enemy), NULL);
	enemy->path = malloc(10 * sizeof(t_vector *));
	if (!enemy->path)
		return (ft_free_enemy(enemy), NULL);
	return (enemy);
}
