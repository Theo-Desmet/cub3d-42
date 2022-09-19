/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:44 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/19 10:58:24 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_strafe(t_game *game)
{
	t_game	*g;

	g = game;
	if (g->right)
	{
		if (g->player->pos->x + g->plane->x >= 0.5 && g->player->pos->x
			+ g->plane->x <= g->map->width - 0.5)
			g->player->pos->x += g->plane->x * g->player->walk_speed;
		if (g->player->pos->y + g->plane->y >= 0.5 && g->player->pos->y
			+ g->plane->y <= g->map->width - 0.5)
			g->player->pos->y += g->plane->y * g->player->walk_speed;
	}
	if (g->left)
	{
		if (g->player->pos->x - g->plane->x >= 0.5 && g->player->pos->x
			- g->plane->x <= g->map->width - 0.5)
			g->player->pos->x -= g->plane->x * g->player->walk_speed;
		if (g->player->pos->y - g->plane->y >= 0.5 && g->player->pos->y
			- g->plane->y <= g->map->width - 0.5)
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
	if (game->rotate_left)
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

void	ft_reset_pos(t_game *game)
{
	if (game->player->pos->x < 1.5)
		game->player->pos->x = 1.5;
	if (game->player->pos->y < 1.5)
		game->player->pos->y = 1.5;
	if (game->player->pos->x > game->map->width - 1.5)
		game->player->pos->x = game->map->width - 1.5;
	if (game->player->pos->y > game->map->height - 1.5)
		game->player->pos->y = game->map->height - 1.5;
}

void	ft_move(t_game *game)
{
	t_player	*play;

	play = game->player;
	ft_reset_pos(game);
	if (game->left || game->right)
		ft_strafe(game);
	if (game->forward)
	{
		if (play->pos->x >= 1.5 && play->pos->x <= game->map->width)
			play->pos->x += play->dir->x * play->walk_speed;
		if (play->pos->y >= 1.5 && play->pos->y <= game->map->height)
			play->pos->y += play->dir->y * play->walk_speed;
	}
	if (game->backward)
	{
		if (play->pos->x >= 1.5 && play->pos->x <= game->map->width)
			play->pos->x -= play->dir->x * play->walk_speed;
		if (play->pos->y >= 1.5 && play->pos->y <= game->map->height)
			play->pos->y -= play->dir->y * play->walk_speed;
	}
	if (game->rotate_left || game->rotate_right)
		ft_rotate(game);
}
