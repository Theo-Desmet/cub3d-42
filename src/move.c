/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:44 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/27 18:44:53 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define FAC 4

void	ft_strafe(t_game *game)
{
	t_game	*g;

	g = game;
	if (g->right)
	{
		if (worldMap[(int)(g->player->pos->x + g->plane->x
				* g->player->walk_speed * FAC)][(int)g->player->pos->y] == 0)
			g->player->pos->x += g->plane->x * g->player->walk_speed;
		if (worldMap[(int)g->player->pos->x][(int)(g->player->pos->y
			+ g->plane->y * g->player->walk_speed * FAC)] == 0)
			g->player->pos->y += g->plane->y * g->player->walk_speed;
	}
	if (g->left)
	{
		if (worldMap[(int)(g->player->pos->x - g->plane->x
				* g->player->walk_speed * FAC)][(int)g->player->pos->y] == 0)
			g->player->pos->x -= g->plane->x * g->player->walk_speed;
		if (worldMap[(int)g->player->pos->x][(int)(g->player->pos->y
			- g->plane->y * g->player->walk_speed * FAC)] == 0)
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
		if (worldMap[(int)(player->pos->x + player->dir->x \
			* player->walk_speed * FAC)][(int)(player->pos->y)] == 0)
			player->pos->x += player->dir->x * player->walk_speed;
		if (worldMap[(int)(player->pos->x)][(int)(player->pos->y \
			+ player->dir->y * player->walk_speed * FAC)] == 0)
			player->pos->y += player->dir->y * player->walk_speed;
	}
	if (game->backward)
	{
		if (worldMap[(int)(player->pos->x - player->dir->x \
			* player->walk_speed * FAC)][(int)player->pos->y] == 0)
			player->pos->x -= player->dir->x * player->walk_speed;
		if (worldMap[(int)player->pos->x][(int)(player->pos->y \
			- player->dir->y * player->walk_speed * FAC)] == 0)
			player->pos->y -= player->dir->y * player->walk_speed;
	}
	if (game->rotate_left || game->rotate_right)
		ft_rotate(game);
}
