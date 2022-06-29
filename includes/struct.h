/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:16:46 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/29 10:39:44 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	int	floor;
	int	ceiling;
	t_img	*w_east;
	t_img	*w_weast;
	t_img	*w_south;
	t_img	*w_north;
}	t_assets;

typedef struct s_check
{
	int	east;
	int	weast;
	int	north;
	int	south;
	int	floor;
	int	ceiling;
	int	spwan;
}	t_check;

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

typedef struct s_player
{
	int		x;
	int		y;
	int		dir;
	int		move;

}	t_player;

typedef struct s_enemy
{
	t_img	*img_b;
	t_img	*img_f;
	int		dir;
	int		on_wall;
}	t_enemy;

typedef struct s_data
{
	t_assets	*assets;
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_enemy		*enemy;
	int			sprite_size;
	void		*mlx;
	void		*win;
	int			c_tick;
	int			e_tick;
}	t_data;

#endif
