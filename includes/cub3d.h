/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:14:31 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/10 10:43:12 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include "../libft/includes/libft.h"
# include "struct.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "define.h"
# include "parsing.h"
# include <stdbool.h>

# define MOVING_SPEED 0.08
# define ROTATE_SPEED 0.04

/* -------------------------------------------------------------------------- */
/*                             FILE = src/utils.c                             */
/* -------------------------------------------------------------------------- */
void			ft_free_textures(t_game *game);
void			ft_update_heading(t_game *game, double x, double y);
void			ft_update_player(t_game *game);
void			ft_fill_error_msg(char **arr);
void			ft_dda(t_ray *ray);

/* -------------------------------------------------------------------------- */
/*                            FILE = src/drawing.c                            */
/* -------------------------------------------------------------------------- */
void			ft_put_pixel(t_img *img, int x, int y, int color);
int				ft_clamp(int x, int low, int high);
unsigned int	ft_get_pixel(t_img *img, int x, int y);

/* -------------------------------------------------------------------------- */
/*                             FILE = src/main.c                              */
/* -------------------------------------------------------------------------- */
unsigned long	ft_get_time(void);
void			ft_fps(t_game *game);
int				main(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                             FILE = src/init2.c                             */
/* -------------------------------------------------------------------------- */
t_game			*ft_alloc_game(void);
t_map			*ft_alloc_map(void);
char			**ft_init_error_messages(void);
t_game			*ft_init_game(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                             FILE = src/move.c                              */
/* -------------------------------------------------------------------------- */
int				ft_tiles(t_game *game, int x, int y);
void			ft_strafe(t_game *game);
void			ft_rotate(t_game *game);
void			ft_move(t_game *game);

/* -------------------------------------------------------------------------- */
/*                     FILE = src/raycasting/raycasting.c                     */
/* -------------------------------------------------------------------------- */
t_render		*ft_init_render(void);
void			ft_render(t_game *game);

/* -------------------------------------------------------------------------- */
/*                       FILE = src/raycasting/floor.c                        */
/* -------------------------------------------------------------------------- */
void			ft_draw_sky_floor(t_game *game, t_render *render);

/* -------------------------------------------------------------------------- */
/*                        FILE = src/raycasting/ray.c                         */
/* -------------------------------------------------------------------------- */
void			ft_prepare_ray(t_game *game, int x);
void			ft_get_wall_tex(t_ray *ray, t_render *render, t_game *game);
void			ft_wall_hit(t_ray *ray, t_game *game);
void			ft_prepare_proj(t_game *game, t_render *render);
void			ft_wall_proj(t_ray *ray, t_render *render, t_game *game);

/* -------------------------------------------------------------------------- */
/*                           FILE = src/cleaning.c                            */
/* -------------------------------------------------------------------------- */
void			ft_free_assets(t_assets *assets, void *mlx);
void			ft_free_player(t_player *player);
void			ft_free_ray(t_ray *ray);
void			ft_free_map(t_game *game, int i);
int				ft_free_all(t_game *game);

/* -------------------------------------------------------------------------- */
/*                             FILE = src/init.c                              */
/* -------------------------------------------------------------------------- */
t_img			*ft_init_img(void *mlx, char *path, int width, int height);
t_assets		*ft_init_assets(t_game *game, void *mlx);
t_vector		*ft_init_vector(double x, double y);
t_ray			*ft_init_ray(void);
t_player		*ft_init_player(void);

/* -------------------------------------------------------------------------- */
/*                              FILE = src/key.c                              */
/* -------------------------------------------------------------------------- */
int				ft_key_down(int keycode, t_game *game);
int				ft_key_up(int keycode, t_game *game);
int				ft_loop(t_game *game);

#endif
