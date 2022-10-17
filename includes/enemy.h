/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:38:45 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/17 11:39:11 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H
# include "struct.h"

/* -------------------------------------------------------------------------- */
/*                        FILE = src/enemy/init_enemy.c                       */
/* -------------------------------------------------------------------------- */
void		ft_free_enemy(t_enemy *enemy, t_game *game);
t_sprite	*ft_create_enemy(t_game *game);
t_enemy		*ft_init_enemy(t_game *game);

/* -------------------------------------------------------------------------- */
/*                        FILE = src/enemy/move_enemy.c                       */
/* -------------------------------------------------------------------------- */
int			ft_ftoi(float f);
int			ft_update_path(t_enemy *enemy, t_map *map, int x, int y);
void		ft_move_enemy(t_enemy *enemy, t_map *map);

/* -------------------------------------------------------------------------- */
/*                        FILE = src/enemy/utils_enemy.c                      */
/* -------------------------------------------------------------------------- */
void		ft_reset_path(t_enemy *enemy);
int			ft_signs(int nb);
void		ft_next_path(t_vector **path, int mov, int i, int dir);
void		ft_path_prev(t_vector **path, int *prev_x, int *prev_y, int i);
int			ft_valide_path(int **map, int y, int x);

/* -------------------------------------------------------------------------- */
/*                        FILE = src/enemy/random.c                           */
/* -------------------------------------------------------------------------- */
int			ft_is_valide_place(t_map *map, int x, int y);
void		ft_random_mod(int *x, int *y);
void		ft_spawn_enemy(t_game *game);
void		ft_random_place(t_enemy *enemy, t_map *map);

/* -------------------------------------------------------------------------- */
/*                        FILE = src/enemy/pathfinding.c                      */
/* -------------------------------------------------------------------------- */
void		ft_hori_mov(t_vector **path, int **map, int i, t_vector *mov);
void		ft_vert_mov(t_vector **path, int **map, int i, t_vector *mov);
void		ft_search_path(t_enemy *enemy, int **map, int i);
void		ft_pathfinding(t_game *game, t_enemy *enemy, t_map *map);

#endif
