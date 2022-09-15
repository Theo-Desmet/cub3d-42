/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/15 14:47:23 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_init_dir(t_game *game)
{
	game->forward = false;
	game->backward = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;
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
			if (game->map->map[i][j] == 2 ||game->map->map[i][j] == 5)
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
	return (res);
}

int	ft_type_object(t_game *game, t_object *obj, int i, int j)
{
	if (game->map->map[i][j] == 2)
	{
		obj->objects[obj->index++] = ft_init_sprite(game, i + 0.5, j + 0.5, game->assets->obj);
		if (!obj->objects[obj->index - 1])
			return (ft_free_obj_tab(obj), -1);
		obj->objects[obj->index - 1]->h_div = 1;
		obj->objects[obj->index - 1]->v_div = 1;
		obj->objects[obj->index - 1]->v_offset = 0;
		}
	else if (game->map->map[i][j] == 5)
	{
		obj->objects[obj->index++] = ft_init_sprite(game, i + 0.5, j + 0.5
		, game->assets->wall_E);
		if (!obj->objects[obj->index - 1])
			return (ft_free_obj_tab(obj), -1);
		obj->objects[obj->index - 1]->h_div = 1;
		obj->objects[obj->index - 1]->v_div = 1;
		obj->objects[obj->index - 1]->v_offset = -128;
	}
	return (0);
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
	objs->zbuff = (double *)malloc(sizeof(double) * screenWidth);
	objs->dist = (double *)malloc(sizeof(double) * objs->nb_obj);
	objs->order = (int *)malloc(sizeof(int) * objs->nb_obj);
	if (!objs->objects || !objs->zbuff || !objs->dist || !objs->order)
		return (ft_free_obj(objs), NULL);
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
	game->doors = malloc(sizeof(t_door *) * game->nb_doors);
	if (!game->doors)
		return (NULL);
	return (game->doors);
}

t_door	**ft_get_doors(t_game *game)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	game->nb_doors = 0;
	ft_alloc_doors(game);
	x = -1;
	while (++x < game->map->height)
	{
		y = -1;
		while (++y < game->map->width)
		{
			if (game->map->map[x][y] == 3)
			{
				game->doors[i] = ft_init_door(x, y);
				if (!game->doors[i])
					return (NULL); //FREE ALL
				i++;

			}
		}
	}
	return (game->doors);
}

void	printTab(int **tab, int x, int y)
{
	int i = 0;
	while (i < x)
	{
		int j = 0;
		while (j < y)
		{
			printf("%d", tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_update_heading(t_game *game, double x, double y)
{
	double half_fov;

	half_fov = FOV / 2;
	game->player->dir->x = x;
	game->player->dir->y = y;
	game->plane->x = -y * ((half_fov * M_PI) / 180);
	game->plane->y = x * ((half_fov * M_PI) / 180);
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

t_game	*ft_init_game(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), NULL);
	game->img = ft_init_img(game->mlx, NULL, screenWidth, screenHeight);
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3D");
	game->map = malloc(sizeof(t_map));
	game->map->width = 0;
	game->map->height = 0;
	game->plane = ft_init_vector(0, 0);
	game->player = ft_init_player();
	game->frame = 0;
	game->textures_path = malloc(4 * sizeof(char *));
	ft_parsing(game, ac, av);
	printf("%d - %d\n", game->map->width, game->map->height);
	ft_update_player(game);
	game->assets = ft_init_assets(game, game->mlx);
	game->ray = ft_init_ray();
	game->object = ft_init_obj(game);
	game->doors	= ft_get_doors(game);
	ft_init_dir(game);
	if (!game->win || !game->assets || !game->player || !game->ray
		|| !game->plane || !game->object || !game->doors || !game->textures_path)
		return (ft_free_all(game), NULL);
	return (game);
}
