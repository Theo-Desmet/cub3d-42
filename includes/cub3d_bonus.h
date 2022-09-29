/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2022/09/29 12:12:13 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../mlx_linux/mlx.h"
# include "../libft/includes/libft.h"
# include "struct.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "define.h"
# include "parsing.h"

int		ft_parsing(t_game *data, int argc, char **argv);
t_door	*ft_get_cur_door(t_game *game, int x, int y);

/* -------------------------------------------------------------------------- */
/*                           FILE = bonus/minimap.c                           */
/* -------------------------------------------------------------------------- */
t_vector	*ft_vector_dup(t_vector *vector);
void	ft_draw_player_minimap(t_game *game);
int	ft_trans(int color, int back);
void	ft_draw_trans(t_game *game, t_vector *vector, int size, int color);
void	ft_color_minimap(t_game *game, int *data);
void	ft_draw_minimap(t_game *game);

/* -------------------------------------------------------------------------- */
/*                          FILE = bonus/cleaning.c                           */
/* -------------------------------------------------------------------------- */
void	ft_free_assets(t_assets *assets, void *mlx);
void	ft_free_player(t_player *player);
void	ft_free_ray(t_ray *ray);
void	ft_free_obj_tab(t_game *game, t_object *obj);
void	ft_free_obj(t_game *game, t_object *obj);

/* -------------------------------------------------------------------------- */
/*                             FILE = bonus/key.c                             */
/* -------------------------------------------------------------------------- */
int	ft_key_down(int keycode, t_game *game);
int	ft_key_up(int keycode, t_game *game);
int	ft_loop(t_game *game);

/* -------------------------------------------------------------------------- */
/*                        FILE = bonus/drawing_utils.c                        */
/* -------------------------------------------------------------------------- */
int		ft_rgbtoi(int r, int g, int b);
void	ft_itorgb(int val, int *r, int *g, int *b);
void	ft_fog(double dist, int *color);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/init.c                             */
/* -------------------------------------------------------------------------- */
t_img	*ft_init_img(void *mlx, char *path, int width, int height);
t_assets	*ft_init_assets(t_game *game, void *mlx);
t_vector	*ft_init_vector(double x, double y);
t_player	*ft_init_player(void);
t_ray	*ft_init_ray(void);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/move.c                             */
/* -------------------------------------------------------------------------- */
int	ft_is_valid_tiles(t_game *game, int x, int y);
void	ft_strafe(t_game *game);
void	ft_rotate(t_game *game);
void	ft_move(t_game *game);

/* -------------------------------------------------------------------------- */
/*                           FILE = bonus/drawing.c                           */
/* -------------------------------------------------------------------------- */
void	ft_put_pixel(t_img *img, int x, int y, int color);
unsigned int	ft_get_pixel(t_img *img, int x, int y);
void	ft_paint(t_img *element, t_img *mlx_img, t_vector *pos, int scale);
void	ft_draw_square2(t_img *img, t_vector *pos, int size, int color);

/* -------------------------------------------------------------------------- */
/*                       FILE = bonus/raycasting/ray.c                        */
/* -------------------------------------------------------------------------- */
void	ft_prepare_ray(t_game *game, int x);
void	ft_dda(t_ray *ray);
void	ft_harbor(t_ray *ray, t_render *render, t_game *game);
void	ft_door_hit(t_ray *ray, t_render *render, t_game *game);
void	ft_get_wall_tex(t_ray *ray, t_render *render, t_game *game);
void	ft_wall_hit(t_ray *ray, t_render *render, t_game *game);
void	ft_prepare_proj(t_game *game, t_render *render);
void	ft_wall_proj(t_ray *ray, t_render *render, t_game *game);

/* -------------------------------------------------------------------------- */
/*                    FILE = bonus/raycasting/raycasting.c                    */
/* -------------------------------------------------------------------------- */
int	ft_free_all(t_game *game);
t_render	*ft_init_render(void);
void	ft_sprite_cast(t_game *game);
void	ft_render(t_game *game);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/raycasting/sprite.c                      */
/* -------------------------------------------------------------------------- */
void	ft_swap(double *a, double *b);
void	ft_sort_sprite(t_object *obj);
void	ft_prepare_sprite(t_game *game, t_object *obj, int *i);
void	ft_color_sprite(t_game *game, int x, int y, int i);
void	ft_draw_sprite(t_game *game, t_object *obj, int i);

/* -------------------------------------------------------------------------- */
/*                      FILE = bonus/raycasting/floor.c                       */
/* -------------------------------------------------------------------------- */
int	ft_modulo(int x);
void	ft_color_floor(t_game *game, t_render *render);
void	ft_floor(t_game *game, t_render *render);
void	ft_floor_wall(t_ray *ray, t_render *render);
void	ft_draw_sky_floor(t_game *game, t_render *render);
void	ft_wall_color(t_game *game, t_ray *ray, t_render *render);

/* -------------------------------------------------------------------------- */
/*                            FILE = bonus/init2.c                            */
/* -------------------------------------------------------------------------- */
void	ft_init_bool(t_game *game);
t_object	*ft_alloc_objs(t_game *game, t_object *obj);
void	ft_get_objs(t_game *game, t_object *obj);
t_object	*ft_init_obj(t_game *game);
t_door	*ft_init_door(int x, int y);
t_door	**ft_alloc_doors(t_game *game);
t_door	**ft_get_doors(t_game *game);
t_game	*ft_init_game(int ac, char **av);


#endif
