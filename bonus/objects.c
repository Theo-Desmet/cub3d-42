/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:13:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/11 19:37:34 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		return (ft_free_obj(objs), NULL);
	return (objs);
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
	if (game->enemy_spw)
		obj->nb_obj++;
	obj->objects = ft_calloc(obj->nb_obj + 1, sizeof(t_sprite *));
	if (!obj->objects)
		return (NULL);
	obj->index = 0;
	return (obj);
}

int	ft_type_object(t_game *game, t_object *obj, int i, int j)
{
	if (game->map->map[i][j] == 2)
	{
		obj->objects[obj->index] = ft_init_sprite(game, j + 0.5,
				i + 0.5, game->assets->obj);
		if (!obj->objects[obj->index])
			return (ft_free_obj_tab(obj), -1);
		obj->objects[obj->index]->animated = true;
		obj->objects[obj->index++]->type = BARREL;
	}
	else if (game->map->map[i][j] == LIGHT)
	{
		obj->objects[obj->index] = ft_init_sprite(game, j + 0.5,
				i + 0.5, game->assets->light);
		if (!obj->objects[obj->index])
			return (ft_free_obj_tab(obj), -1);
		obj->objects[obj->index++]->type = LIGHT;
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
			if (ft_type_object(game, obj, i, j) == -1)
				return ;
	}
	if (game->enemy_spw)
		obj->objects[obj->index] = ft_create_enemy(game);
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
	res->h_div = 1;
	res->v_div = 1;
	res->v_offset = 0;
	return (res);
}
