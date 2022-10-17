/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2022/10/17 15:24:02 by bbordere         ###   ########.fr       */
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
# include "enemy.h"
# include "define.h"
# include "parsing.h"
# include <sys/time.h>

# define MOVING_SPEED 0.15
# define ROTATE_SPEED 0.06

/* -------------------------------------------------------------------------- */
/*                          FILE = bonus/cleaning2.c                          */
/* -------------------------------------------------------------------------- */
void			ft_free_sprite(t_sprite *sprite);
void			ft_free_obj_tab(t_object *obj);
void			ft_free_obj(t_object *obj);
void			ft_free_textures(t_game *game);
void			ft_free_visual(t_game *game);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/enemy.c                            */
/* -------------------------------------------------------------------------- */
t_sprite		*ft_create_enemy(t_game *game);
t_enemy			*ft_init_enemy(t_game *game);

/* -------------------------------------------------------------------------- */
/*                           FILE = bonus/objects.c                           */
/* -------------------------------------------------------------------------- */
t_object		*ft_init_obj(t_game *game);
t_object		*ft_alloc_objs(t_game *game, t_object *obj);
int				ft_type_object(t_game *game, t_object *obj, int i, int j);
t_sprite		*ft_create_enemy(t_game *game);
int				ft_get_objs(t_game *game, t_object *obj);
t_sprite		*ft_init_sprite(t_game *game, double x, double y, t_img *img);

/* -------------------------------------------------------------------------- */
/*                         FILE = bonus/door_utils.c                          */
/* -------------------------------------------------------------------------- */
void			ft_side1(t_ray *ray, t_render *render, t_game *game);
void			ft_side0(t_ray *ray, t_render *render, t_game *game);
void			ft_door_handler(t_game *game);
t_door			*ft_init_door(int x, int y);
t_door			**ft_alloc_doors(t_game *game);

/* -------------------------------------------------------------------------- */
/*                           FILE = bonus/drawing.c                           */
/* -------------------------------------------------------------------------- */
void			ft_put_pixel(t_img *img, int x, int y, int color);
int				ft_clamp(int x, int low, int high);
unsigned int	ft_get_pixel(t_img *img, int x, int y);
void			ft_draw_square(t_game *game, t_square square);
void			ft_draw_line(t_game *game, t_vector *pos, t_vector *pos2,
					int color);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/main.c                             */
/* -------------------------------------------------------------------------- */
int				ft_parsing(t_game *game, int argc, char **argv);;
int				mouse_handling(int x, int y, t_game *game);
unsigned long	ft_get_time(void);
void			ft_fps(t_game *game);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/init3.c                            */
/* -------------------------------------------------------------------------- */
t_door			**ft_get_doors(t_game *game);
void			ft_update_heading(t_game *game, double x, double y);
void			ft_update_player(t_game *game);
t_game			*ft_alloc_game(void);
void			ft_fill_error_msg(char **arr);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/init2.c                            */
/* -------------------------------------------------------------------------- */
int				ft_free_all(t_game *game);
char			**ft_init_error_messages(void);
t_map			*ft_alloc_map(void);
t_game			*ft_init_primary(t_game *game);
t_game			*ft_init_game(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/move.c                             */
/* -------------------------------------------------------------------------- */
int				ft_tiles(t_game *game, int x, int y);
void			ft_strafe(t_game *game);
void			ft_rotate(t_game *game);
void			ft_move(t_game *game);

/* -------------------------------------------------------------------------- */
/*                    FILE = bonus/raycasting/raycasting.c                    */
/* -------------------------------------------------------------------------- */
void			ft_sprite_cast(t_game *game);
void			ft_draw_gun(t_game *game, int frame);
void			ft_gun(t_game *game);
void			ft_render(t_game *game);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/raycasting/sprite.c                      */
/* -------------------------------------------------------------------------- */
t_sprite		*ft_get_cur_sprite(t_game *game);
void			ft_update_cur_obj(t_object *obj, t_sprite *cur);
void			ft_prepare_sprite(t_game *game, t_object *obj, int *i);
void			ft_color_sprite(t_game *game, int x, int y, int i);
void			ft_draw_sprite(t_game *game, t_object *obj, int i);

/* -------------------------------------------------------------------------- */
/*                 FILE = bonus/raycasting/utils_raycasting.c                 */
/* -------------------------------------------------------------------------- */
double			ft_clampf(double x, double low, double high);
void			ft_prepare_ray(t_game *game, int x);
void			ft_dda(t_ray *ray);
void			ft_get_wall_tex(t_ray *ray, t_render *render, t_game *game);
void			ft_particular_wall_hit(t_game *game, t_render *render,
					t_ray *ray);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/raycasting/floor.c                       */
/* -------------------------------------------------------------------------- */
void			ft_color_floor(t_game *game, t_render *render);
void			hehe(t_game *game, t_render *render);
void			ft_color_ceil(t_game *game, t_render *render);
void			ft_floor(t_game *game, t_render *render);
void			ft_floor_wall(t_ray *ray, t_render *render);

/* -------------------------------------------------------------------------- */
/*                       FILE = bonus/raycasting/ray.c                        */
/* -------------------------------------------------------------------------- */
void			ft_wall_hit(t_ray *ray, t_render *render, t_game *game);
void			ft_prot_render(t_render *render);
void			ft_prepare_proj(t_game *game, t_render *render);
void			ft_door_proj(t_ray *ray, t_render *render, t_door *door);
void			ft_wall_proj(t_ray *ray, t_render *render, t_game *game);

/* -------------------------------------------------------------------------- */
/*                   FILE = bonus/raycasting/utils_render.c                   */
/* -------------------------------------------------------------------------- */
void			ft_swap(double *a, double *b);
void			ft_sort_sprite(t_object *obj);
int				ft_modulo(int x);
void			ft_wall_color(t_game *game, t_ray *ray, t_render *render);

/* -------------------------------------------------------------------------- */
/*                          FILE = bonus/cleaning.c                           */
/* -------------------------------------------------------------------------- */
void			ft_free_assets(t_assets *assets, void *mlx);
void			ft_free_player(t_player *player);
void			ft_free_enemy(t_enemy *enemy, t_game *game);
void			ft_free_ray(t_ray *ray);
void			ft_destroy_img(t_img *img, void *mlx);
void			ft_free_map(t_game *game, int i);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/init.c                             */
/* -------------------------------------------------------------------------- */
t_img			*ft_init_img(void *mlx, char *path, int width, int height);
t_assets		*ft_init_assets(t_game *game, void *mlx);
t_vector		*ft_init_vector(double x, double y);
t_player		*ft_init_player(void);
t_ray			*ft_init_ray(void);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/door.c                             */
/* -------------------------------------------------------------------------- */
t_door			*ft_get_cur_door(t_game *game, int x, int y);
void			ft_harbor(t_ray *ray, t_render *render, t_game *game);
void			ft_upd_x_off(t_ray *ray, t_render *render, t_game *game,
					t_door *door);
void			ft_upd_y_off(t_ray *ray, t_render *render, t_game *game,
					t_door *door);
void			ft_door_hit(t_ray *ray, t_render *render, t_game *game);

/* -------------------------------------------------------------------------- */
/*                           FILE = bonus/minimap.c                           */
/* -------------------------------------------------------------------------- */
bool			ft_is_in_limit(double x, double y, int radius, int mode);
void			ft_draw_player(t_game *game, int color);
void			ft_draw_tiles(t_game *game, t_square square, int x, int y);
void			ft_draw_minimap(t_game *game);

/* -------------------------------------------------------------------------- */
/*                        FILE = bonus/drawing_utils.c                        */
/* -------------------------------------------------------------------------- */
int				ft_rgbtoi(int r, int g, int b);
void			ft_itorgb(int val, int *r, int *g, int *b);
void			ft_color_fog(int *color, t_rgb *rgb, double intensity);
void			ft_fog(double dist, int *color);
int				ft_transp(int color, int back);

/* -------------------------------------------------------------------------- */
/*                             FILE = bonus/key.c                             */
/* -------------------------------------------------------------------------- */
int				ft_key_down(int keycode, t_game *game);
void			ft_door(t_game *game);
int				ft_key_up(int keycode, t_game *game);
void			ft_animation_handler(t_object *obj, int i);
int				ft_loop(t_game *game);

#endif
