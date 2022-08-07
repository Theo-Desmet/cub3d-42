/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/07/20 15:43:01 by bbordere         ###   ########.fr       */
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

t_object	*ft_alloc_objs(t_object *obj)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
			if (worldMap[i][j] == 2)
				obj->nb_obj++;
	}
	obj->objects = malloc(sizeof(t_vector) * obj->nb_obj);
	if (!obj->objects)
		return (NULL);
	obj->index = 0;
	i = -1;
	while (++i < obj->nb_obj)
		obj->objects[i] = NULL;
	return (obj);
}

void	ft_get_objs(t_object *obj)
{
	int	i;
	int	j;

	i = -1;
	ft_alloc_objs(obj);
	if (!obj->objects)
		return ;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
		{
			if (worldMap[i][j] == 2)
			{
				obj->objects[obj->index++] = ft_init_vector(i + 0.5, j + 0.5);
				if (!obj->objects[obj->index - 1])
				{
					ft_free_obj_tab(obj);
					return ;
				}
			}
		}
	}
}

t_object	*ft_init_obj(t_game *game)
{
	t_object	*objs;

	(void)game;
	objs = malloc(sizeof(t_object));
	if (!objs)
		return (NULL);
	objs->nb_obj = 0;
	objs->objects = NULL;
	ft_get_objs(objs);
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

	door = malloc(sizeof(door));
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
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
			if (worldMap[i][j] == 3)
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
	while (++x < mapWidth)
	{
		y = -1;
		while (++y < mapHeight)
		{
			if (worldMap[x][y] == 3)
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

t_game	*ft_init_game(void)
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
	game->assets = ft_init_assets(game->mlx);
	game->player = ft_init_player();
	game->ray = ft_init_ray();
	game->plane = ft_init_vector(1, 0); // fov=1=90 N : y=fov, S : -fov, E x=fov, W x=-fov 
	game->object = ft_init_obj(game);
	game->doors	= ft_get_doors(game);
	ft_init_dir(game);
	if (!game->win || !game->assets || !game->player || !game->ray
		|| !game->plane || !game->object || !game->doors)
		return (ft_free_all(game), NULL);
	return (game);
}
