/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:16:46 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/21 12:38:58 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

#define screenWidth 1200
#define screenHeight 600

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_assets
{
	t_img	*wall_E;
	t_img	*wall_W;
	t_img	*wall_N;
	t_img	*wall_S;
	t_img	*floor;
	t_img	*ceil;
	t_img	*gun;
	t_img	*obj;
}	t_assets;

typedef struct s_map
{
	int		x;
	int		y;
	int		width;
	int		start;
	int		height;
	int	**map;
	int		fd_map;
}	t_map;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef	struct s_render
{
	int		x;
	int		y;
	int		start;
	int		end;
	int		sprite_x;
	int		sprite_y;
	int		color;
	int		height_line;
	double	wall_x;
	double	perp_wall_dist;

	double	floor_x;
	double	floor_y;
	double	weight;
	double	cur_x;
	double	cur_y;
	double	dist_player;
	double	cur_dist;
}	t_render;

typedef struct s_ray
{
	double	camera_x;
	double	ddx;
	double	ddy;
	double	sidedist_x;
	double	sidedist_y;
	int		hit;
	int		side;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	t_vector	*dir;
	t_vector	*pos;
}	t_ray;

typedef struct s_player
{
	t_vector *pos;
	t_vector *dir;
	double walk_speed;
	double rot_speed;
}	t_player;

typedef struct s_enemy
{
	t_img	*img_b;
	t_img	*img_f;
	int		dir;
	int		on_wall;
}	t_enemy;

typedef struct s_object
{
	double		*zbuff;
	int			*order;
	double		*dist;
	double		s_x;
	double		s_y;
	double		tr_x;
	double		tr_y;
	double		inv;
	double		h_div;
	double		v_div;
	double		v_offset;
	int			move_screen;
	int			screen_x;
	int			s_height;
	int			s_width;
	int			start_y;
	int			end_y;
	int			start_x;
	int			end_x;
	int			tex_x;
	int			tex_y;
	int			d;
	int			color;
	t_vector	**objects;
	int			nb_obj;
	int			index;
}	t_object;

typedef struct s_game
{
	t_assets	*assets;
	t_vector	*plane;
	
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_ray		*ray;
	t_object	*object;
	void		*mlx;
	void		*win;
	bool		forward;
	bool		backward;
	bool		left;
	bool		right;
	bool		rotate_left;
	bool		rotate_right;
}	t_game;

#endif
