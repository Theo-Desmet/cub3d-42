/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/05 13:54:44 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_init_bool(t_game *game)
{
	game->forward = false;
	game->backward = false;
	game->left = false;
	game->right = false;
	game->r_left = false;
	game->r_right = false;
	game->mouse_right = false;
	game->mouse_left = false;
	game->shooting = false;
}

t_object	*ft_alloc_objs(t_game *game, t_object *obj)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
			if (game->map->map[i][j] == 2 || game->map->map[i][j] == 5)
				obj->nb_obj++;
	}
	obj->objects = malloc(sizeof(t_sprite) * obj->nb_obj);
	if (!obj->objects)
		return (NULL);
	obj->index = 0;
	i = -1;
	while (++i < obj->nb_obj)
		obj->objects[i] = NULL;
	return (obj);
}

t_sprite	*ft_init_sprite(t_game *game, double x, double y, t_img *img)
{
	t_sprite	*res;

	(void)game;
	res = malloc(sizeof(t_sprite));
	if (!res)
		return (NULL);
	res->pos = ft_init_vector(x, y);
	if (!res->pos)
		return (free(res), NULL);
	res->last_pos = ft_init_vector(x, y);
	if (!res->pos)
		return (free(res->pos), free(res), NULL);
	res->texture = img;
	res->frame = 0;
	res->animated = false;
	return (res);
}

enum e_type_sprite
{
	BARREL = 2,
	LIGHT = 5,
	GUN = 6
};

int	ft_type_object(t_game *game, t_object *obj, int i, int j)
{
	if (game->map->map[i][j] == 2)
	{
		obj->objects[obj->index++] = ft_init_sprite(game, j + 0.5,
				i + 0.5, game->assets->obj);
		if (!obj->objects[obj->index - 1])
			return (ft_free_obj_tab(game, obj), -1);
		obj->objects[obj->index - 1]->h_div = 1;
		obj->objects[obj->index - 1]->v_div = 1;
		obj->objects[obj->index - 1]->v_offset = 0;
		obj->objects[obj->index - 1]->animated = true;
		}
	else if (game->map->map[i][j] == LIGHT)
	{
		t_img	*light = ft_init_img(game->mlx, "assets/greenlight.xpm", 64, 64);
		obj->objects[obj->index++] = ft_init_sprite(game, j + 0.5,
				i + 0.5, light);
		if (!obj->objects[obj->index - 1])
			return (ft_free_obj_tab(game, obj), -1);
		obj->objects[obj->index - 1]->h_div = 1;
		obj->objects[obj->index - 1]->v_div = 1;
		obj->objects[obj->index - 1]->v_offset = 0;
	}
	return (0);
}

t_enemy	*ft_init_enemy(void)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
			return (NULL);
	enemy->act = malloc(sizeof(t_vector));
	if (!enemy->act)
			return (ft_free_enemy(enemy), NULL);
	enemy->act->x = 1;//spawn a mdf
	enemy->act->y = 1;//spawn a mdf
<<<<<<< HEAD
        enemy->dest = malloc(sizeof(t_vector));
        if (!enemy->dest)
                return (ft_free_enemy(enemy), NULL);
        enemy->img_enemy = malloc(sizeof(t_img));
        if (!enemy->img_enemy)
                return (ft_free_enemy(enemy), NULL);
        enemy->path = malloc(11 * sizeof(t_vector *));
        if (!enemy->path)
                return (ft_free_enemy(enemy), NULL);
=======
	enemy->dest = malloc(sizeof(t_vector));
	if (!enemy->dest)
		return (ft_free_enemy(enemy), NULL);
	enemy->img_enemy = malloc(sizeof(t_img));
	if (!enemy->img_enemy)
		return (ft_free_enemy(enemy), NULL);
	enemy->path = malloc(10 * sizeof(t_vector *));
	if (!enemy->path)
		return (ft_free_enemy(enemy), NULL);
>>>>>>> bbordere
	return (enemy);
}

void	ft_get_objs(t_game *game, t_object *obj)
{
	int	i;
	int	j;

	i = -1;
	ft_alloc_objs(game, obj);
	if (!obj->objects)
		return ;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
		{
			if (ft_type_object(game, obj, i, j) == -1)
				return ;
		}
	}
}

void	ft_free_sprite(t_game *game, t_sprite *sprite)
{
	if (sprite->texture)
	{
		mlx_destroy_image(game->mlx, sprite->texture->mlx_img);
		free(sprite->texture);
	}
	if (sprite->pos)
		free(sprite->pos);
	if (sprite->last_pos)
		free(sprite->last_pos);
	free(sprite);
}

void	ft_free_obj_tab(t_game *game, t_object *obj)
{
	int	i;

	i = 0;
	while (i < obj->nb_obj)
	{
		if (obj->objects[i])
			ft_free_sprite(game, obj->objects[i]);
		i++;
	}
	free(obj->objects);
	obj->objects = NULL;
}

void	ft_free_obj(t_game *game, t_object *obj)
{
	if (obj->zbuff)
		free(obj->zbuff);
	if (obj->dist)
		free(obj->dist);
	if (obj->objects)
		ft_free_obj_tab(game, obj);
	if (obj->order)
		free(obj->order);
	free(obj);
}

t_object	*ft_init_obj(t_game *game)
{
	t_object	*objs;

	objs = malloc(sizeof(t_object));
	if (!objs)
		return (NULL);
	objs->tick = 0;
	objs->nb_obj = 0;
	objs->objects = NULL;
	ft_get_objs(game, objs);
	objs->index = 0;
	objs->zbuff = malloc(sizeof(double) * S_WIDTH);
	objs->dist = malloc(sizeof(double) * objs->nb_obj);
	objs->order = malloc(sizeof(int) * objs->nb_obj);
	if (!objs->objects || !objs->zbuff || !objs->dist || !objs->order)
		return (ft_free_obj(game, objs), NULL);
	return (objs);
}

t_door	*ft_init_door(int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	if (!door)
		return (NULL);
	door->x = x;
	door->y = y;
	door->factor = 0;
	door->state = 1;
	return (door);
}

t_door	**ft_alloc_doors(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
			if (game->map->map[i][j] == 3)
				game->nb_doors++;
	}
	game->doors = (t_door **)ft_calloc(game->nb_doors + 1, sizeof(t_door *));
	if (!game->doors)
		return (NULL);
	return (game->doors);
}

void	ft_free_map(t_game *game, int i)
{
	if (game->map->map)
		while (i >= 0)
			free(game->map->map[i--]);
	free(game->map->map);
	free(game->map);
}

void	ft_free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		free(game->textures_path[i++]);
	free(game->textures_path);
}

void	ft_free_visual(t_game *game)
{
	if (game->ray)
		ft_free_ray(game->ray);
	if (game->assets)
		ft_free_assets(game->assets, game->mlx);
	if (game->player)
		ft_free_player(game->player);
	if (game->object)
		ft_free_obj(game, game->object);
	if (game->doors)
		ft_free_tab((void **)game->doors);
	if (game->img)
	{
		mlx_destroy_image(game->mlx, game->img->mlx_img);
		free(game->img);
	}
}

int	ft_free_all(t_game *game)
{
	ft_free_visual(game);
	if (game->plane)
		free(game->plane);
	if (game->textures_path)
		ft_free_textures(game);
	if (game->map)
		ft_free_map(game, game->map->height - 1);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->error_msg)
		ft_free_tab((void **)game->error_msg);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

t_door	**ft_get_doors(t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	game->nb_doors = 0;
	ft_alloc_doors(game);
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->map[y][x] == 3)
			{
				game->doors[i] = ft_init_door(x, y);
				if (!game->doors[i])
					return (ft_free_tab((void **)game->doors), NULL);
				i++;
			}
		}
	}
	return (game->doors);
}

void	ft_update_heading(t_game *game, double x, double y)
{
	game->player->dir->x = x;
	game->player->dir->y = y;
	game->plane->x = -y * ((FOV / 2 * M_PI) / 180);
	game->plane->y = x * ((FOV / 2 * M_PI) / 180);
}

void	ft_update_player(t_game *game)
{
	game->player->pos->x = (double)game->player->parsed_x + 0.5;
	game->player->pos->y = (double)game->player->parsed_y + 0.5;
	if (game->player->heading == 'W')
		ft_update_heading(game, -1.0, 0.0);
	else if (game->player->heading == 'E')
		ft_update_heading(game, 1.0, 0.0);
	else if (game->player->heading == 'S')
		ft_update_heading(game, 0.0, 1.0);
	else
		ft_update_heading(game, 0.0, -1.0);
}

t_game	*ft_alloc_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->assets = NULL;
	game->plane = NULL;
	game->map = NULL;
	game->img = NULL;
	game->player = NULL;
	game->ray = NULL;
	game->object = NULL;
	game->doors = NULL;
	game->mlx = NULL;
	game->textures_path = NULL;
	game->win = NULL;
	game->error_msg = NULL;
	ft_init_bool(game);
	return (game);
}

void	ft_fill_error_msg(char **arr)
{
	arr[NO_FILE] = ft_strdup("bad file: please add an file with .cub"
			" extension\n");
	arr[TOO_MANY_FILE] = ft_strdup("bad file: too many files, please use"
			" only one\n");
	arr[BAD_EXTENSION] = ft_strdup("bad extension file: filename need .cub"
			" extension\n");
	arr[BAD_FORMAT] = ft_strdup("bad filename: please use a valid filename\n");
	arr[NOT_FOUND] = ft_strdup("bad filename: file not found\n");
	arr[INVALID_SYNTAX] = ft_strdup(": use or redifine of an invalide syntax\n");
	arr[INVALID_CHAR] = ft_strdup(": use of an invalid char on map\n");
	arr[MULTI_SPAWN] = ft_strdup(": redifine of spawn, please use only one\n");
	arr[NO_SPAWN] = ft_strdup("error in file: no spawn in map\n");
	arr[COPY_ERROR] = ft_strdup("error during the copy of the map\n");
	arr[INVALID_HEADER] = ft_strdup("error in file: invalid line in head\n");
}

char	**ft_init_error_messages(void)
{
	char	**arr;
	int		i;

	arr = (char **)ft_calloc(12, sizeof(char *));
	if (!arr)
		return (NULL);
	ft_fill_error_msg(arr);
	i = -1;
	while (++i < 11)
		if (!arr[i])
			return (ft_free_tab((void **)arr), NULL);
	return (arr);
}

t_map	*ft_alloc_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->fd_map = -1;
	map->map = NULL;
	return (map);
}

t_game	*ft_init_game(int ac, char **av)
{
	t_game	*game;

	game = ft_alloc_game();
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), NULL);
	game->map = ft_alloc_map();
	game->textures_path = (char **)ft_calloc(4, sizeof(char *));
	game->player = ft_init_player();
	game->enemy = ft_init_enemy();
	game->error_msg = ft_init_error_messages();
	game->plane = ft_init_vector(1, 0);
	if (!game->map || !game->textures_path || !game->player || !game->plane
		|| !game->error_msg || !ft_parsing(game, ac, av))
		return (ft_free_all(game), NULL);
	ft_update_player(game);
	srand(time(NULL));
	ft_spawn_enemy(game);
	game->assets = ft_init_assets(game, game->mlx);
	if (!game->assets)
		return (ft_free_all(game), NULL);
	game->ray = ft_init_ray();
	game->object = ft_init_obj(game);
	game->img = ft_init_img(game->mlx, NULL, S_WIDTH, S_HEIGHT);
	game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "cub3D");
	game->frame = 50;
	game->doors = ft_get_doors(game);
	if (!game->ray || !game->object || !game->img
		|| !game->win || !game->doors)
		return (ft_free_all(game), NULL);
	return (game);
}
