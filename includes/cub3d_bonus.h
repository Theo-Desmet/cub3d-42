/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2022/10/05 14:24:25 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../mlx_linux/mlx.h"
# include "../libft/includes/libft.h"
# include "struct.h"
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include <stdio.h>
# include <math.h>
# include "define.h"
# include "parsing.h"

# define MOVING_SPEED 0.15
# define ROTATE_SPEED 0.06

int				ft_parsing(t_game *data, int argc, char **argv);
t_door			*ft_get_cur_door(t_game *game, int x, int y);
void			ft_random_place(t_enemy *enemy, t_map *map);
void			ft_pathfinding(t_game *game, t_enemy *enemy, t_map *map);
void			ft_spawn_enemy(t_game *game);

/* -------------------------------------------------------------------------- */
/*                           FILE = bonus/minimap.c                           */
/* -------------------------------------------------------------------------- */
int				ft_trans(int color, int back);
bool			ft_is_in_limit(double x, double y, int radius, int mode);
void			ft_draw_square(t_game *game, t_square square);
void			ft_draw_line(t_game *game, t_vector *pos, t_vector *pos2,
					int color);
void			ft_draw_player(t_game *game, int color);
void			ft_draw_tiles(t_game *game, t_square square, int x, int y);
void			ft_draw_minimap(t_game *game);

/* -------------------------------------------------------------------------- */
/*                          FILE = bonus/cleaning.c                           */
/* -------------------------------------------------------------------------- */
void			ft_free_assets(t_assets *assets, void *mlx);
void			ft_free_player(t_player *player);
void			ft_free_enemy(t_enemy *enemy);
void			ft_free_ray(t_ray *ray);

/* -------------------------------------------------------------------------- */
/*                             FILE = bonus/key.c                             */
/* -------------------------------------------------------------------------- */
int				ft_key_down(int keycode, t_game *game);
void			ft_door(t_game *game);
int				ft_key_up(int keycode, t_game *game);
void			ft_animation_handler(t_object *obj, int i);
int				ft_loop(t_game *game);

/* -------------------------------------------------------------------------- */
/*                        FILE = bonus/drawing_utils.c                        */
/* -------------------------------------------------------------------------- */
int				ft_rgbtoi(int r, int g, int b);
void			ft_itorgb(int val, int *r, int *g, int *b);
void			ft_fog(double dist, int *color);

/* -------------------------------------------------------------------------- */
/*                     FILE = bonus/parsing/pathfinding.c                     */
/* -------------------------------------------------------------------------- */
int				ft_signs(int nb);
void			ft_next_path(t_vector **path, int mov, int i, int dir);
void			ft_path_prev(t_vector **path, int *prev_x, int *prev_y, int i);
void			ft_hori_mov(t_vector **path, int **map, int i, t_vector *mov);
void			ft_vert_mov(t_vector **path, int **map, int i, t_vector *mov);
void			ft_search_path(t_enemy *enemy, int **map, int i);
int				ft_ftoi(float f);
void    		ft_move_enemy(t_enemy *enemy, t_map *map);
void			ft_pathfinding(t_game *game, t_enemy *enemy, t_map *map);

/* -------------------------------------------------------------------------- */
/*                   FILE = bonus/parsing/check_map_head.c                    */
/* -------------------------------------------------------------------------- */
int				ft_check_map_head(t_game *game, char *line, t_check *check);
int				ft_check_is_head(char *str);
int				ft_check_valid_head(t_game *game, t_check *check);

/* -------------------------------------------------------------------------- */
/*                       FILE = bonus/parsing/parsing.c                       */
/* -------------------------------------------------------------------------- */
size_t			ft_get_texture_index(const char *id);
int				ft_check_valid_path(t_game *game, const char *line,
					const char *str);
char			*ft_getpath(const char *line);
int				ft_check_ext_file(t_game *game, char *str, char *ext);
int				ft_parsing(t_game *game, int argc, char **argv);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/parsing/check_map.c                      */
/* -------------------------------------------------------------------------- */
int				ft_check_map(t_game *game, char *line, t_check *check,
					int line_cnt);
int				ft_is_valid_map_line(t_game *game, char *line);
int				ft_check_spawn(t_game *game, char *line, int spawn,
					int line_cnt);
t_check			*ft_init_check(t_check *check);
int				ft_check_file(t_game *game, int fd, t_check *check);

/* -------------------------------------------------------------------------- */
/*                       FILE = bonus/parsing/random.c                        */
/* -------------------------------------------------------------------------- */
int				ft_is_valide_place(t_enemy *enemy, t_map *map, int x, int y);
void			ft_mod_size(t_map *map, int *mod_x, int *mod_y);
void			ft_random_mod(t_map *map, int *x, int *y);
void			ft_spawn_enemy(t_game *game);
void			ft_random_place(t_enemy *enemy, t_map *map);

/* -------------------------------------------------------------------------- */
/*                    FILE = bonus/parsing/check_border.c                     */
/* -------------------------------------------------------------------------- */
int				ft_check_border(t_game *game, int **map);
int				ft_check_is_a_border(t_game *game, int **map, int x, int y);

/* -------------------------------------------------------------------------- */
/*                       FILE = bonus/parsing/atorgb.c                        */
/* -------------------------------------------------------------------------- */
int				ft_check_is_rgb(char *line, char *str);
int				ft_atorgb(char *str);

/* -------------------------------------------------------------------------- */
/*                     FILE = bonus/parsing/err_parsing.c                     */
/* -------------------------------------------------------------------------- */
void			ft_err_file_name(t_game *game, int argc, int error);
char			*ft_get_error_msg(t_game *game, int error);
void			ft_err_in_file(t_game *game, t_check *check, int error,
					int line);
void			ft_err_copy_map(t_game *game, int nb_line);
void			ft_err_bordere(int x, int y);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/parsing/fill_map.c                       */
/* -------------------------------------------------------------------------- */
int				*ft_fill_line(t_game *game, char *line, int *map);
int				**ft_fill_map(t_game *game, int **map, char *line, int fd);
int				ft_copy_map(t_game *game, int **map, char *path);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/init.c                             */
/* -------------------------------------------------------------------------- */
t_img			*ft_init_img(void *mlx, char *path, int width, int height);
t_assets		*ft_init_assets(t_game *game, void *mlx);
t_vector		*ft_init_vector(double x, double y);
t_player		*ft_init_player(void);
t_ray			*ft_init_ray(void);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/move.c                             */
/* -------------------------------------------------------------------------- */
int				ft_tiles(t_game *game, int x, int y);
void			ft_strafe(t_game *game);
void			ft_rotate(t_game *game);
void			ft_move(t_game *game);

/* -------------------------------------------------------------------------- */
/*                           FILE = bonus/drawing.c                           */
/* -------------------------------------------------------------------------- */
void			ft_put_pixel(t_img *img, int x, int y, int color);
int				ft_clamp(int x, int low, int high);
unsigned int	ft_get_pixel(t_img *img, int x, int y);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/door.c                             */
/* -------------------------------------------------------------------------- */
t_door			*ft_get_cur_door(t_game *game, int x, int y);
void			ft_side1(t_ray *ray, t_render *render, t_game *game);
void			ft_side0(t_ray *ray, t_render *render, t_game *game);
void			ft_harbor(t_ray *ray, t_render *render, t_game *game);
void			ft_upd_x_off(t_ray *ray, t_render *render, t_game *game,
					t_door *door);
void			ft_upd_y_off(t_ray *ray, t_render *render, t_game *game,
					t_door *door);
void			ft_door_hit(t_ray *ray, t_render *render, t_game *game);

/* -------------------------------------------------------------------------- */
/*                       FILE = bonus/raycasting/ray.c                        */
/* -------------------------------------------------------------------------- */
void			ft_prepare_ray(t_game *game, int x);
void			ft_dda(t_ray *ray);
void			ft_get_wall_tex(t_ray *ray, t_render *render, t_game *game);
void			ft_particular_wall_hit(t_game *game, t_render *render,
					t_ray *ray);
void			ft_wall_hit(t_ray *ray, t_render *render, t_game *game);
void			ft_prot_render(t_render *render);
void			ft_prepare_proj(t_game *game, t_render *render);
void			ft_door_proj(t_ray *ray, t_render *render, t_door *door);
void			ft_wall_proj(t_ray *ray, t_render *render, t_game *game);

/* -------------------------------------------------------------------------- */
/*                    FILE = bonus/raycasting/raycasting.c                    */
/* -------------------------------------------------------------------------- */
t_render		*ft_init_render(void);
void			ft_update_sprite(t_game *game, t_sprite *sprite);
void			ft_sprite_cast(t_game *game);
void			ft_draw_square(t_game *game, t_square square);;
void			ft_draw_gun(t_game *game, int frame);
void			ft_gun(t_game *game);
void			ft_render(t_game *game);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/raycasting/sprite.c                      */
/* -------------------------------------------------------------------------- */
void			ft_swap(double *a, double *b);
void			ft_sort_sprite(t_object *obj);
t_sprite		*ft_get_cur_sprite(t_game *game);
void			ft_update_cur_obj(t_object *obj, t_sprite *cur);
void			ft_prepare_sprite(t_game *game, t_object *obj, int *i);
void			ft_color_sprite(t_game *game, int x, int y, int i);
void			ft_draw_sprite(t_game *game, t_object *obj, int i);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/raycasting/floor.c                       */
/* -------------------------------------------------------------------------- */
int				ft_modulo(int x);
void			ft_color_floor(t_game *game, t_render *render);
void			ft_floor(t_game *game, t_render *render);
void			ft_floor_wall(t_ray *ray, t_render *render);
void			ft_wall_color(t_game *game, t_ray *ray, t_render *render);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/init2.c                            */
/* -------------------------------------------------------------------------- */
void			ft_init_bool(t_game *game);
t_object		*ft_alloc_objs(t_game *game, t_object *obj);
t_sprite		*ft_init_sprite(t_game *game, double x, double y, t_img *img);
int				ft_type_object(t_game *game, t_object *obj, int i, int j);
t_enemy			*ft_init_enemy(void);
void			ft_get_objs(t_game *game, t_object *obj);
void			ft_free_sprite(t_game *game, t_sprite *sprite);
void			ft_free_obj_tab(t_game *game, t_object *obj);
void			ft_free_obj(t_game *game, t_object *obj);
t_object		*ft_init_obj(t_game *game);
t_door			*ft_init_door(int x, int y);
t_door			**ft_alloc_doors(t_game *game);
void			ft_free_map(t_game *game, int i);
void			ft_free_textures(t_game *game);
void			ft_free_visual(t_game *game);
int				ft_free_all(t_game *game);
t_door			**ft_get_doors(t_game *game);
void			ft_update_heading(t_game *game, double x, double y);
void			ft_update_player(t_game *game);
t_game			*ft_alloc_game(void);
void			ft_fill_error_msg(char **arr);
char			**ft_init_error_messages(void);
t_map			*ft_alloc_map(void);
t_game			*ft_init_game(int ac, char **av);

#endif
