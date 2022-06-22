/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:49:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/21 17:40:03 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

#define SPRITE_SIZE 64
#define mapWidth 25
#define mapHeight 25
#define screenWidth 1200
#define screenHeight 600

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,2,0,0,0,0,0,0,2,2,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,1},
	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1},
	{1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1},
	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/* INIT */

t_img	*ft_init_img(void *mlx, char *path, int width, int height)
{
	t_img	*img;
	int		size;

	size = SPRITE_SIZE;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	if (path)
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size, &size);
	else
		img->mlx_img = mlx_new_image(mlx, width, height);
	if (!img->mlx_img)
		return (NULL);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		return (NULL);
	return (img);
}

t_assets	*ft_init_assets(void *mlx)
{
	t_assets	*asset;

	asset = malloc(sizeof(t_assets));
	if (!asset)
		return (NULL);
	asset->wall_E = ft_init_img(mlx, "bluestone.xpm", 0, 0);
	asset->wall_N = ft_init_img(mlx, "eagle.xpm", 0, 0);
	asset->wall_S = ft_init_img(mlx, "greystone.xpm", 0, 0);
	asset->wall_W = ft_init_img(mlx, "redbrick.xpm", 0, 0);
	asset->ceil = ft_init_img(mlx, "wood.xpm",0, 0);
	asset->floor = ft_init_img(mlx, "colorstone.xpm", 0, 0);
	asset->gun = ft_init_img(mlx, "gun.xpm", 0, 0);
	asset->obj = ft_init_img(mlx, "barrel.xpm", 0, 0);
	if (!asset->wall_E || !asset->wall_N || !asset->wall_S || !asset->wall_W || !asset->gun || !asset->ceil || !asset->floor)
		// return (ft_free_assets(asset, mlx));
		return (NULL);
	return (asset);
}

t_vector	*ft_init_vector(double x, double y)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_player	*ft_init_player()
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->dir = ft_init_vector(-1, 0);
	player->pos = ft_init_vector(11, 3);
	player->rot_speed = 0.033;
	player->walk_speed = 0.08;
	if (!player->dir || !player->pos)
		// return (ft_free_player(player))
		return (NULL);
	return (player);
}

t_ray		*ft_init_ray(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->camera_x = 0.0;
	ray->ddx = 0.0;
	ray->ddy = 0.0;
	ray->sidedist_x = 0.0;
	ray->sidedist_y = 0.0;
	ray->hit = 0;
	ray->side = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->pos = ft_init_vector(0.0, 0.0);
	ray->dir = ft_init_vector(0.0, 0.0);
	if (!ray->dir || !ray->pos)
		return (NULL); //FREEE
	return (ray);
}

void		ft_init_dir(t_game *game)
{
	game->forward = false;
	game->backward = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;
}

void		ft_get_objs(t_game *game, t_object *object, int mode)
{
	int	i;
	int	j;
	
	i = -1;
	object->index = 0;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
		{
			if (worldMap[i][j] == 2)
			{
				if (mode)
					object->nb_obj++;
				else
					object->objects[object->index++] = ft_init_vector((double)i + 0.5, (double)j + 0.5);
			}
		}
	}
	if (mode)
	{
		object->objects = malloc(sizeof(t_vector) * object->nb_obj);
		ft_get_objs(game, object, 0);
	}
}

t_object	*ft_init_obj(t_game *game)
{
	t_object	*objs;

	objs = malloc(sizeof(t_object));
	if (!objs)
		return (NULL);	
	objs->nb_obj = 0;
	ft_get_objs(game, objs, 1);
	objs->index = 0;
	objs->zbuff = malloc(sizeof(double) * screenWidth);
	objs->dist = malloc(sizeof(double) * objs->nb_obj);
	objs->order = malloc(sizeof(int) * objs->nb_obj);
	if (!objs->objects || !objs->zbuff)
		return (NULL);
	
	return (objs);
}

t_game		*ft_init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (NULL); // protect + error
	game->img = ft_init_img(game->mlx, NULL, screenWidth, screenHeight);
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "Hello world!");
	game->assets = ft_init_assets(game->mlx);
	game->player = ft_init_player();
	game->ray = ft_init_ray();
	game->plane = ft_init_vector(0, 1);
	game->object = ft_init_obj(game);
	ft_init_dir(game);
	return (game);
}



#define FAC 4

void	ft_strafe(t_game *game)
{
	if (game->right)
	{
		if (worldMap[(int)(game->player->pos->x + game->plane->x
			* game->player->walk_speed * FAC)][(int)game->player->pos->y] == 0)
			game->player->pos->x += game->plane->x * game->player->walk_speed;
		if (worldMap[(int)game->player->pos->x][(int)(game->player->pos->y
			+ game->plane->y * game->player->walk_speed * FAC)] == 0)
			game->player->pos->y += game->plane->y * game->player->walk_speed;
	}
	if (game->left)
	{
		if (worldMap[(int)(game->player->pos->x - game->plane->x
			* game->player->walk_speed * FAC)][(int)game->player->pos->y] == 0)
			game->player->pos->x -= game->plane->x * game->player->walk_speed;
		if (worldMap[(int)game->player->pos->x][(int)(game->player->pos->y
			- game->plane->y * game->player->walk_speed * FAC)] == 0)
			game->player->pos->y -= game->plane->y * game->player->walk_speed;
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

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	unsigned int	color;
	char			*pix;

	pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pix;
	return (color);
}

void	ft_draw_square(t_img *img, t_vector *pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			ft_put_pixel(img, (int)pos->x + i, (int)pos->y + j, color);
			j++;
		}
		i++;
	}
}

void	ft_prepare_ray(t_game *game, int x)
{
	t_ray	*ray;

	ray = game->ray;
	ray->camera_x = 2.0 * (double)x / (double)screenWidth - 1.0;
	ray->dir->x = game->player->dir->x + game->plane->x * ray->camera_x;
	ray->dir->y = game->player->dir->y + game->plane->y * ray->camera_x;

	// ray->ddx = sqrt(1.0 + pow(ray->dir->y, 2.0) / pow(ray->dir->x, 2.0));
	// ray->ddy = sqrt(1.0 + pow(ray->dir->x, 2.0) / pow(ray->dir->y, 2.0));

	ray->ddx = fabs(1 / ray->dir->x);
	ray->ddy = fabs(1 / ray->dir->y);

	ray->pos->x = game->player->pos->x; 
	ray->pos->y = game->player->pos->y;
	ray->map_x = (int)ray->pos->x;
	ray->map_y = (int)ray->pos->y;
	ray->hit = 0;
}

void	ft_dda(t_ray *ray)
{
	if (ray->dir->x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->pos->x - ray->map_x) * ray->ddx;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->pos->x) * ray->ddx;
	}
	if (ray->dir->y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->pos->y - ray->map_y) * ray->ddy;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->pos->y) * ray->ddy;
	}
}

void	ft_draw_line(t_img *img, t_vector *pos, t_vector *pos2);

void	ft_wall_hit(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->ddx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->ddy;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (worldMap[ray->map_x][ray->map_y] == 1)
			ray->hit = 1;
	}
}

void	ft_floor(t_game *game, t_render *render)
{

	render->y = 0;
	t_vector	dir0;
	t_vector	dir1;
	while (render->y < screenHeight)
	{
		
		dir0.x = game->player->dir->x - game->plane->x;
		dir0.y = game->player->dir->y - game->plane->y;
		dir1.x = game->player->dir->x + game->plane->x;
		dir1.y = game->player->dir->y + game->plane->y;

		int p = render->y - screenHeight / 2;
		double posZ = (double)screenHeight * 0.5;
		double row_dist = posZ / (double)p;
		double f_stepX = row_dist * (dir1.x - dir0.x) / screenWidth;
		double f_stepY = row_dist * (dir1.y - dir0.y) / screenWidth;
		double floor_x = game->player->pos->x + row_dist * dir0.x;
		double floor_y = game->player->pos->y + row_dist * dir0.y;

		for (int x = 0; x < screenWidth; x++)
		{
			int cellx = (int)floor_x;
			int	celly = (int)floor_y;
			
			int	tx = (int)((double)SPRITE_SIZE * (floor_x - cellx) * 1) % SPRITE_SIZE;
			int	ty = (int)((double)SPRITE_SIZE * (floor_y - celly) * 1) % SPRITE_SIZE;

			floor_x += f_stepX;
			floor_y += f_stepY;

			ft_put_pixel(game->img, x, render->y, ft_get_pixel(game->assets->floor, tx, ty));
			ft_put_pixel(game->img, x, screenHeight - render->y - 1, ft_get_pixel(game->assets->ceil, tx, ty));
		}
		render->y++;
	}
}

void	ft_floor_wall(t_ray *ray, t_render *render)
{
	if (ray->side == 0 && ray->dir->x > 0)
	{
		render->floor_x = (double)ray->map_x;
		render->floor_y = (double)ray->map_y + render->wall_x;
	}
	else if (ray->side == 0 && ray->dir->x < 0)
	{
		render->floor_x = (double)ray->map_x + 1.0;
		render->floor_y = (double)ray->map_y + render->wall_x;
	}
	else if (ray->side == 1 && ray->dir->y > 0)
	{
		render->floor_x = (double)ray->map_x + render->wall_x;
		render->floor_y = (double)ray->map_y;
	}
	else
	{
		render->floor_x = (double)ray->map_x + render->wall_x;
		render->floor_y = (double)ray->map_y + 1.0;
	}
}

void	ft_prepare_proj(t_game *game, t_render *render)
{
	t_ray	*ray;

	ray = game->ray;
	if (game->ray->side == 0)
		render->perp_wall_dist = game->ray->sidedist_x - game->ray->ddx;
	else
		render->perp_wall_dist = game->ray->sidedist_y - game->ray->ddy;
	// if (game->ray->side == 0)
	// 	perp_wall_dist = (((double)game->ray->map_x - game->ray->pos->x + (1.0 - (double)game->ray->step_x) / 2.0) / game->ray->dir->x);
	// else
	// 	perp_wall_dist = (((double)game->ray->map_y - game->ray->pos->y + (1.0 - (double)game->ray->step_y) / 2.0) / game->ray->dir->y);
	render->height_line = ((int)((double)screenHeight / render->perp_wall_dist));
	render->start = - (render->height_line) / 2 + screenHeight / 2;
	render->end = render->height_line / 2 + screenHeight / 2;
	if (render->start < 0)
		render->start = 0;
	if (render->end >= screenHeight)
		render->end = screenHeight - 1;	
	if (render->end < 0)
		render->end = screenHeight;
	if (game->ray->side == 1)
		render->wall_x = ray->pos->x + (((double)ray->map_y - ray->pos->y 
			+ (1.0 - (double)ray->step_y) / 2.0) / ray->dir->y) * ray->dir->x;
	else
		render->wall_x = ray->pos->y + (((double)ray->map_x - ray->pos->x 
			+ (1.0 - (double)ray->step_x) / 2.0) / ray->dir->x) * ray->dir->y;
	render->wall_x -= floor(render->wall_x);
	render->sprite_x = (int)(render->wall_x * (double)SPRITE_SIZE);
}

void	ft_draw_sky_floor(t_game *game, t_render *render)
{
	render->y = render->end;
	while (render->y < screenHeight)
	{
		ft_put_pixel(game->img, render->x, render->y, 0x4C5270); // SOL
		// ft_put_pixel(game->img, render->x, render->y, 0); // SOL
		ft_put_pixel(game->img, render->x, screenHeight - render->y - 1, 0x00D1D1); // CIEL
		// ft_put_pixel(game->img, render->x, screenHeight - render->y - 1, 0); // CIEL
		render->y++;
	}


}

void	ft_wall_color(t_game *game, t_ray *ray, t_render *render)
{
	render->color = ft_get_pixel(game->assets->wall_S, \
		render->sprite_x, render->sprite_y);
	if (ray->side == 1 && ray->dir->y < 0)
		render->color = ft_get_pixel(game->assets->wall_W, \
			render->sprite_x, render->sprite_y);
	else if (ray->side == 1 && ray->dir->y > 0)
		render->color = ft_get_pixel(game->assets->wall_E, \
			render->sprite_x, render->sprite_y);
	else if (ray->side == 0 && ray->dir->x > 0)
		render->color = ft_get_pixel(game->assets->wall_N,\
			render->sprite_x, render->sprite_y);
	if (ray->side == 1)
		render->color = (render->color >> 1) & 0x7F7F7F;	
}

void	ft_wall_proj(t_ray *ray, t_render *render, t_game *game)
{

	// render->y = render->start;
	// while (render->y < render->end)
	// {
	// 	if (game->ray->side == 1)
	// 		ft_put_pixel(game->img, render->x, render->y, 0xCCCCCC);
	// 	else
	// 		ft_put_pixel(game->img, render->x, render->y, 0xf2f2f2);
	// 	render->y++;
	// }

	ft_prepare_proj(game, render);
	if (ray->side == 0 && ray->dir->x > 0.0)
		render->sprite_x = SPRITE_SIZE - render->sprite_x - 1;
	if (ray->side == 1 && ray->dir->y < 0.0)
		render->sprite_x = SPRITE_SIZE - render->sprite_x - 1;
	render->y = render->start;
	while (render->y < render->end)
	{
		render->sprite_y = (render->y * 2 - screenHeight + render->height_line)
			* (SPRITE_SIZE / 2) / render->height_line;
		ft_wall_color(game, ray, render);
		ft_put_pixel(game->img, render->x, render->y, render->color);
		render->y++;
	}
}

t_render	*ft_init_render(void)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	render->end = 0;
	render->start = 0;
	render->x = 0;
	render->y = 0;
	render->color = 0;
	render->sprite_x = 0;
	render->sprite_y = 0;
	render->wall_x = 0;
	return (render);
}

void	ft_paint(t_img *element, t_img *mlx_img, t_vector *pos, int scale)
{
	int				x1;
	int				y1;
	unsigned int	color;
	int				save;

	y1 = 0;
	save = (int)pos->x;
	while (y1 < SPRITE_SIZE)
	{
		pos->x = save;
		x1 = 0;
		while (x1 < SPRITE_SIZE)
		{
			color = ft_get_pixel(element, x1, y1);
			if (!(color == (unsigned int)(0xFF << 24)))
				ft_draw_square(mlx_img, pos, scale, color);
			pos->x += scale;
			x1++;
		}
		pos->y += scale;
		y1++;
	}	
}

//////////////////////////////////////////////////////////////////////////////////////

void	ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_sprite(t_object *obj)
{
	int		i;
	int		j;
	int	temp;

	i = -1;
	while (++i < obj->nb_obj)
	{
		j = -1;
		while (++j < obj->nb_obj)
		{
			if (obj->dist[j + 1] > obj->dist[j])
			{
				ft_swap(&obj->dist[j + 1], &obj->dist[j]);
				temp = obj->order[j + 1];
				obj->order[j + 1] = obj->order[j];
				obj->order[j] = temp;
			}
		}
	}
	
}

void	ft_prepare_sprite(t_game *game, t_object *obj, int *i)
{
	obj->s_x = obj->objects[obj->order[*i]]->x - game->player->pos->x;
	obj->s_y = obj->objects[obj->order[*i]]->y - game->player->pos->y;
	obj->inv = 1.0 / (game->plane->x * game->player->dir->y
		- game->player->dir->x * game->plane->y);
	obj->tr_x = obj->inv * (game->player->dir->y * obj->s_x
		- game->player->dir->x * obj->s_y);
	obj->tr_y = obj->inv * (-(game->plane->y) * obj->s_x
		+ game->plane->x * obj->s_y);
	obj->move_screen = (int)(obj->v_offset / obj->tr_y);
	obj->screen_x = (int)((screenWidth / 2) * (1 + obj->tr_x / obj->tr_y));
	obj->s_height = abs((int)(screenHeight / (obj->tr_y))) / obj->v_div;
	obj->start_y = -obj->s_height / 2 + screenHeight / 2 + obj->move_screen;
	if (obj->start_y < 0)
		obj->start_y = 0;
	obj->end_y = obj->s_height / 2 + screenHeight / 2 + obj->move_screen;
	if (obj->end_y >= screenHeight)
		obj->end_y = screenHeight - 1;
	obj->s_width = abs((int)(screenHeight / (obj->tr_y))) / obj->h_div;
	obj->start_x = -obj->s_width / 2 + obj->screen_x;
	if (obj->start_x < 0)
		obj->start_x = 0;
	obj->end_x = obj->s_width / 2 + obj->screen_x;
	if (obj->end_x >= screenWidth)
		obj->end_x = screenWidth - 1;
}

void	ft_draw_sprite(t_game *game, t_object *obj)
{
	int	x;
	int	y;

	x = obj->start_x - 1;
	while (++x < obj->end_x)
	{
		obj->tex_x = (int)(256 * (x - (-obj->s_width / 2 + obj->screen_x))
			* SPRITE_SIZE / obj->s_height) / 256;
		if (obj->tr_y > 0 && x > 0 && x < screenWidth && obj->tr_y < obj->zbuff[x])
		{
			y = obj->start_y - 1;
			while (++y < obj->end_y)
			{
				obj->d = (y - obj->move_screen) * 256 - screenHeight
					* 128 + obj->s_height * 128;
				obj->tex_y = ((obj->d * SPRITE_SIZE) / obj->s_height) / 256;
				obj->color = ft_get_pixel(game->assets->obj,
					obj->tex_x, obj->tex_y);
				if (obj->color != (0xFF << 24))
					ft_put_pixel(game->img, x, y, obj->color);
			}
		}
	}
}

void	ft_sprite_cast(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->object->nb_obj)
	{
		game->object->order[i] = i;
		game->object->dist[i] = (pow(game->player->pos->x - game->object->objects[i]->x, 2)
			+ pow(game->player->pos->y - game->object->objects[i]->y, 2));
		i++;
	}

	ft_sort_sprite(game->object);
	i = -1;
	game->object->h_div = 1;
	game->object->v_div = 1;
	game->object->v_offset = 0;
	while (++i < game->object->nb_obj)
	{
		ft_prepare_sprite(game, game->object, &i);
		if (game->object->end_x < 0)
			game->object->end_x = 0;
		ft_draw_sprite(game, game->object);
		// for (int stripe = game->object->start_x; stripe < game->object->end_x; stripe++)
		// {
			
		// 	if (game->object->tr_y > 0 && stripe > 0 && stripe < screenWidth && game->object->tr_y < game->object->zbuff[stripe])
		// 	{
		// 		for (int y = game->object->start_y; y < game->object->end_y; y++)
		// 		{
					
		// 		}
		// 	}
		// }		
	}
}


///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

//MINIMAP

void	ft_draw_line(t_img *img, t_vector *pos, t_vector *pos2)
{
	double	dx;
	double	dy;
	int		pixels;
	t_vector	coord;
	
	dx = pos2->x - pos->x;
	dy = pos2->y - pos->y;
	pixels = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
	dx /= pixels;
	dy /= pixels;
	coord.x = pos->x;
	coord.y = pos->y;
	while (pixels)
	{
		// ft_put_pixel(img, coord.x, coord.y, 0xFF0000);
		ft_draw_square(img, &coord, 1, 0x00FF00);
		coord.x += dx;
		coord.y += dy;
		pixels--;
	}
}

void	ft_draw_player_minimap(t_game *game)
{
	int	size = 10;
	ft_draw_square(game->img, ft_init_vector((game->player->pos->x * size), (game->player->pos->y * size)), 8, 0xFF0000);
	ft_draw_line(game->img, ft_init_vector(((game->player->pos->x) * size) + 3, ((game->player->pos->y) * size) + 3),
		ft_init_vector((game->player->pos->x * size + game->player->dir->x * game->player->walk_speed * 400),
			(game->player->pos->y * size + game->player->dir->y * game->player->walk_speed * 400)));
	// ft_draw_line(game->img, ft_init_vector(0, 0), ft_init_vector(100, 100));
	
}

void	ft_draw_minimap(t_game *game)
{
	int	y;
	int	screen_x = 0;
	int	screen_y;
	int	size = 10;
	int	x;

	y = -1;
	screen_y = 0;

	while (++y < mapHeight)
	{
		x = -1;
		screen_x = 0;
		while (++x < mapWidth)
		{
			if (worldMap[x][y] == 1)
				ft_draw_square(game->img, ft_init_vector(screen_x, screen_y), size, 0);
			else if (worldMap[x][y] == 2)
				ft_draw_square(game->img, ft_init_vector(screen_x, screen_y), size, 0x00FFFF);
			else
				ft_draw_square(game->img, ft_init_vector(screen_x, screen_y), size, 0xFFFFFF);
			screen_x += size;
		}
		screen_y += size;
		ft_draw_player_minimap(game);
	}
}

///////////////////////////////////////////////////////////////////////////////
void	ft_render(t_game *game)
{

	t_render	*render;

	render = ft_init_render();
	if (!render)
		return ;
	ft_move(game);

	ft_floor(game, render);

	while (render->x < screenWidth)
	{
		ft_prepare_ray(game, render->x);
		ft_dda(game->ray);
		ft_wall_hit(game->ray);
		
		ft_wall_proj(game->ray, render, game);

		// ft_draw_sky_floor(game, render);

		game->object->zbuff[render->x] = render->perp_wall_dist;
		render->x++;
	}
	ft_sprite_cast(game);
	ft_paint(game->assets->gun, game->img, ft_init_vector((screenWidth / 2) - 32 * 8, (screenHeight / 2) - 27 * 8), 8);
	ft_draw_minimap(game);
	
	free(render);
}

int	ft_key_down(int keycode, t_game *game)
{
	if (keycode == 'z')
		game->forward = true;
	if (keycode == 's')
		game->backward = true;
	if (keycode == 'q')
		game->left = true;
	if (keycode == 'd')
		game->right = true;
	if (keycode == 65363)
		game->rotate_right = true;
	if (keycode == 65361)
		game->rotate_left = true;
	return (0);
}

int	ft_key_up(int keycode, t_game *game)
{
	if (keycode == 'z')
		game->forward = false;
	if (keycode == 's')
		game->backward = false;
	if (keycode == 'q')
		game->left = false;
	if (keycode == 'd')
		game->right = false;
	if (keycode == 65363)
		game->rotate_right = false;
	if (keycode == 65361)
		game->rotate_left = false;
	return (0);
}

int	ft_loop(t_game *game)
{
	ft_render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->mlx_img, 0, 0);
	return (0);
}

int main(void)
{
	t_game	*game;

	game = ft_init_game();
	if (!game)
		exit(EXIT_FAILURE);
	mlx_hook(game->win, 2, 1L, ft_key_down, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_up, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	return 0;
}
