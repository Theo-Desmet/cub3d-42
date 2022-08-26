/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:44 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/25 10:32:48 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define FAC 0.5

int	ft_is_valid_tiles(t_game *game, int x, int y)
{
	return (game->map->map[x][y] == 0 || game->map->map[x][y] == 4);
}

void	ft_strafe(t_game *game)
{
	t_game	*g;

	g = game;
	if (g->right)
	{
		if (ft_is_valid_tiles(game, (int)(g->player->pos->x + g->plane->x * FAC), (int)g->player->pos->y))
			g->player->pos->x += g->plane->x * g->player->walk_speed;
		if (ft_is_valid_tiles(game, (int)g->player->pos->x, (int)(g->player->pos->y + g->plane->y * FAC)))
			g->player->pos->y += g->plane->y * g->player->walk_speed;
	}
	if (g->left)
	{
		if (ft_is_valid_tiles(game, (int)(g->player->pos->x - g->plane->x * FAC), (int)g->player->pos->y))
			g->player->pos->x -= g->plane->x * g->player->walk_speed;
		if (ft_is_valid_tiles(game, (int)g->player->pos->x, (int)(g->player->pos->y - g->plane->y * FAC)))
			g->player->pos->y -= g->plane->y * g->player->walk_speed;
	}
}

void	ft_rotate(t_game *game)
{
	double		old_dir_x;
	double		old_plane_x;
	double		r_speed;
	t_player	*p;

	p = game->player;
	if (game->rotate_right)
		r_speed = -p->rot_speed;
	else
		r_speed = p->rot_speed;
	old_dir_x = p->dir->x;
	p->dir->x = p->dir->x * cos(r_speed) - p->dir->y * sin(r_speed);
	p->dir->y = old_dir_x * sin(r_speed) + p->dir->y * cos(r_speed);
	old_plane_x = game->plane->x;
	game->plane->x = game->plane->x * cos(r_speed)
		- game->plane->y * sin(r_speed);
	game->plane->y = old_plane_x * sin(r_speed)
		+ game->plane->y * cos(r_speed);
}

void	ft_move(t_game *game)
{
	t_player	*player;

	player = game->player;
	if (game->left || game->right)
		ft_strafe(game);
	if (game->forward)
	{
		if (ft_is_valid_tiles(game, (int)(player->pos->x + player->dir->x * FAC), (int)(player->pos->y)))
			player->pos->x += player->dir->x * player->walk_speed;

		if (ft_is_valid_tiles(game, (int)(player->pos->x), (int)(player->pos->y + player->dir->y * FAC)))
			player->pos->y += player->dir->y * player->walk_speed;
	}
	if (game->backward)
	{
		if (ft_is_valid_tiles(game, (int)(player->pos->x - player->dir->x * FAC), (int)player->pos->y))
			player->pos->x -= player->dir->x * player->walk_speed;
		if (ft_is_valid_tiles(game, (int)player->pos->x, (int)(player->pos->y \
			- player->dir->y * FAC)))
			player->pos->y -= player->dir->y * player->walk_speed;
	}
	if (game->rotate_left || game->rotate_right)
		ft_rotate(game);
}
