/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:50:28 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/05 14:24:56 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_ftoi(float f)
{
	f = f * 10;
	return ((int)f);
}

void	ft_move_enemy(t_enemy *enemy, t_map *map)
{
	int	path_x;
	int	path_y;
	int	act_x;
	int	act_y;

	path_x = ft_ftoi(enemy->path[enemy->i_path]->x);
	path_y = ft_ftoi(enemy->path[enemy->i_path]->y);
	act_x = ft_ftoi(enemy->act->x);
	act_y = ft_ftoi(enemy->act->y);
	if (path_x == act_x && path_y == act_y)
	{
		map->map[path_x / 10][path_y / 10] = 0;
		enemy->i_path++;
		if (!enemy->path[enemy->i_path])
			return ;
		path_x = ft_ftoi(enemy->path[enemy->i_path]->x);
		path_y = ft_ftoi(enemy->path[enemy->i_path]->y);
		map->map[path_x / 10][path_y / 10] = 7;
	}
	else if (path_x > act_x && path_y == act_y)	
		enemy->act->x += 0.1;
	else if (path_x < act_x && path_y == act_y)	
		enemy->act->x -= 0.1;
	else if (path_y > act_y && path_x == act_x)
		enemy->act->y += 0.1;
	else if (path_y < act_y && path_x == act_x)	
		enemy->act->y -= 0.1;

	// printf("%lf, %lf, %d\n", enemy->act->x, enemy->act->y, enemy->i_path);
}






void	ft_add_list(t_node **list, t_node *new)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	list[i] = new;
}

void	ft_rm_list(t_node **list, t_node *new)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	free(list[i]);
	list[i] = NULL;
}

int	ft_is_in_list(t_node **list, t_node *node)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (list[i]->pos->x == node->pos->x && list[i]->pos->y == node->pos->y)
			return (i);
		i++;
	}
	return (0);
}

void	ft_update_open(t_node **open, t_node *node)
{
	int	i;

	i = ft_is_in_list(open, node);
	if (i > 0 && node->f < open[i]->f)
	{
		free(open[i]);
		open[i] = node;
	}
	else
		ft_add_list(open, node);
}

void	ft_check_node(t_map *map, t_node **close, t_node **open, t_node *node, t_enemy *enemy)
{
	if (node->pos->x < 1 || node->pos->y < 1
			|| node->pos->y > map->height || node->pos->x >map->width)
		return ;

	if ((map->map[(int)node->pos->y][(int)node->pos->x] != 0
			&& map->map[(int)node->pos->y][(int)node->pos->x] != 3))
	{
		if (!ft_is_in_list(close, node))
			ft_add_list(close, node);
		return ;
	}
	if (ft_is_in_list(close, node))
		return ;
	node->h = (pow(enemy->dest->x, 2) - pow(node->pos->x, 2))
		+ (pow(enemy->dest->x, 2) - pow(node->pos->x, 2));
	node->f = node->g + node->h;
	ft_update_open(open, node);	
}

void	ft_check_adj(t_map *map, t_node **close, t_node **open, t_node *node, t_enemy *enemy)
{
	t_node	*temp;
	
	temp = malloc(sizeof(t_node));
	temp->g = node->g + 1;
	temp->parent = node;
	temp->pos->x = node->pos->x - 1;
	temp->pos->y = node->pos->y - 1;
	ft_check_node(map, close, open, temp, enemy);
	temp->pos->x = node->pos->x;
	ft_check_node(map, close, open, temp, enemy);
	temp->pos->x = node->pos->x + 1;
	ft_check_node(map, close, open, temp, enemy);

	temp->pos->x = node->pos->x - 1;
	temp->pos->y = node->pos->y;
	ft_check_node(map, close, open, temp, enemy);
	temp->pos->x = node->pos->x;
	ft_add_list(close, node);
	temp->pos->x = node->pos->x + 1;
	ft_check_node(map, close, open, temp, enemy);

	temp->pos->x = node->pos->x - 1;
	temp->pos->y = node->pos->y + 1;
	ft_check_node(map, close, open, temp, enemy);
	temp->pos->x = node->pos->x;
	ft_check_node(map, close, open, temp, enemy);
	temp->pos->x = node->pos->x + 1;
	ft_check_node(map, close, open, temp, enemy);
}

t_node	*ft_best_node(t_node **open)
{
	int	i;
	t_node	*best;

	i = 0;
	best = open[0];
	while (open[i])
	{
		if (open[i]->f < best->f)
			best = open[i];
		i++;
	}
	return (best);
}

t_vector	**ft_get_path(t_vector **path, t_node	*node)
{
	int	i;

	i = node->g;
	path = malloc((node->g + 1) * sizeof(t_vector *));
	if (!path)
		return (NULL);
	while (node->parent)
	{
		path[i] = node->pos;
		node = node->parent;
		i--;
	}
	return (path);
}

void	ft_pathfinding(t_enemy *enemy, t_map *map)//add secu if no path find
{
	t_node	**close;
	t_node	**open;
	t_node	*act;

	close = malloc(1000000);
	close = ft_memset(close, 0, 1000000);
	open = malloc(1000000);
	open = ft_memset(open, 0, 1000000);
	act = malloc(sizeof(t_node));
	act->pos->x = enemy->act->x;
	act->pos->y = enemy->act->y;
	act->g = 0;
	ft_add_list(open, act);
	while (act->pos->x != enemy->dest->x && act->pos->y != enemy->dest->y)
	{
		act = ft_best_node(open);
		ft_check_adj(map, close, open, act, enemy);
	}
	ft_get_path(enemy->path, act);
}
