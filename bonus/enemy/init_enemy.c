/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:10:09 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/17 15:29:49 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_free_enemy(t_enemy *enemy, t_game *game)
{
	if (enemy->act)
		free(enemy->act);
	if (enemy->dest)
		free(enemy->dest);
	if (enemy->sprite)
	{
		if (enemy->sprite->texture)
			ft_destroy_img(enemy->sprite->texture, game->mlx);
		ft_free_sprite(enemy->sprite);
	}
	if (enemy->path)
		ft_free_tab((void **)enemy->path);
	free(enemy);
}

t_sprite	*ft_create_enemy(t_game *game)
{
	t_img		*enemy;
	t_sprite	*res;

	enemy = ft_init_img(game->mlx, "assets/ennemy.xpm", SP_SIZE * 5,
			SP_SIZE * 5);
	if (!enemy)
		return (NULL);
	res = ft_init_sprite(game, game->enemy->act->x + 0.5,
			game->enemy->act->y + 0.5, enemy);
	if (!res)
		return (NULL);
	res->type = ENEMY;
	res->animated = true;
	game->enemy->sprite = res;
	return (res);
}

t_enemy	*ft_init_enemy(t_game *game)
{
	t_enemy	*enemy;
	size_t	i;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	ft_memset(enemy, 0, sizeof(t_enemy));
	enemy->act = ft_init_vector(0, 0);
	enemy->dest = ft_init_vector(0, 0);
	enemy->sprite = NULL;
	enemy->i_path = -1;
	enemy->path = ft_calloc(11, sizeof(t_vector *));
	if (!enemy->path)
		return (ft_free_enemy(enemy, game), NULL);
	i = 0;
	while (i < 10)
	{
		enemy->path[i++] = ft_init_vector(0, 0);
		if (!enemy->path[i - 1])
			return (ft_free_enemy(enemy, game), NULL);
	}
	if (!enemy->act || !enemy->dest || !enemy->path)
		return (ft_free_enemy(enemy, game), NULL);
	return (enemy);
}
