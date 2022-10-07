/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:16:46 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/07 12:08:34 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdbool.h>

enum	e_size
{
	SP_SIZE = 64,
	S_WIDTH = 1080,
	S_HEIGHT = 540,
	SIZE_GUN = (S_WIDTH / S_HEIGHT) * (S_HEIGHT / SP_SIZE) / 3
};

enum	e_map {
	SIZE_MAP = S_WIDTH / 12,
	VIS = 15,
	SIZE_TILE = (SIZE_MAP * 2) / VIS,
	SIZE_PLAYER = SIZE_MAP / 6,
	LEN_PL = (SIZE_PLAYER)
};


enum	e_error_msg
{
	NO_FILE,
	TOO_MANY_FILE,
	BAD_EXTENSION,
	BAD_FORMAT,
	NOT_FOUND,
	INVALID_SYNTAX,
	INVALID_CHAR,
	MULTI_SPAWN,
	NO_SPAWN,
	COPY_ERROR,
	INVALID_HEADER
};
typedef	struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;


typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_check
{
	int		east;
	int		weast;
	int		north;
	int		south;
	int		floor;
	int		ceiling;
	int		spawn;
	char	*line;
	bool	is_head;
	int		line_cnt;
	int		len_hdr;
}	t_check;

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
	t_img	*door;
}	t_assets;

typedef struct s_map
{
	int		x;
	int		y;
	int		width;
	int		start;
	int		height;
	int		**map;
	int		fd_map;
}	t_map;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_square
{
	t_vector	pos;
	int			size;
	int			color;
	int			mode;
	bool		is_transparent;
}	t_square;

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
	t_img	*wall_tex;
	double	wall_x;
	double	perp_wall_dist;
	double	x_offset;
	double	y_offset;

	double	floor_x;
	double	floor_y;
	double	step_x;
	double	step_y;
	double	row_dist;
	int		tex_y;
	int		tex_x;
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
	t_vector	*pos;
	t_vector	*dir;
	int			parsed_x;
	int			parsed_y;
	char		heading;
	double		walk_speed;
	double		rot_speed;
}	t_player;

typedef struct s_node
{
	t_vector	*pos;
	int		g;
	int		h;
	int		f;
	struct s_node	*parent;
}	t_node;

typedef struct s_enemy
{
	int			i_path;
	t_vector	*act;
	t_vector	*dest;
	t_vector	**path;
	t_img		*img_enemy;
}	t_enemy;

typedef struct s_sprite
{
	t_vector	*pos;
	t_vector	*last_pos;
	t_img		*texture;
	bool		animated;
	int			type;
	int			frame;
	double		h_div;
	double		v_div;
	double		v_offset;
}	t_sprite;

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
	t_sprite	**objects;
	int			nb_obj;
	int			index;
	int			tick;
}	t_object;

typedef struct s_door
{
	int		x;
	int		y;
	double	factor;
	int		state;
}	t_door;

typedef struct s_game
{
	t_assets	*assets;
	t_vector	*plane;
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_enemy		*enemy;
	t_ray		*ray;
	t_object	*object;
	t_door		**doors;
	int			nb_doors;
	int			frame;
	char		**textures_path;
	char		**error_msg;
	void		*mlx;
	void		*win;
	bool		forward;
	bool		backward;
	bool		left;
	bool		right;
	bool		r_left;
	bool		r_right;
	bool		mouse_right;
	bool		mouse_left;
	bool		shooting;
	double		enemy_spw;
	int			ceiling_color;
	int			floor_color;
}	t_game;

#endif
