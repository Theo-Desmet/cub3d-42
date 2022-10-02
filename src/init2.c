/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:40:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/01 14:47:19 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_update_heading(t_game *game, double x, double y)
{
	double	half_fov;

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

t_player	*ft_init_player(t_game *game)
{
	t_player	*player;

	(void)game;
	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->dir = ft_init_vector(0, 0);
	player->pos = ft_init_vector(0, 0);
	player->rot_speed = ROTATE_SPEED;
	player->walk_speed = MOVING_SPEED;
	if (!player->dir || !player->pos)
		return (ft_free_player(player), NULL);
	return (player);
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

int	ft_free_all(t_game *game)
{
	if (game->ray)
		ft_free_ray(game->ray);
	if (game->assets)
		ft_free_assets(game->assets, game->mlx);
	if (game->player)
		ft_free_player(game->player);
	if (game->plane)
		free(game->plane);
	if (game->textures_path)
		ft_free_textures(game);
	if (game->map)
		ft_free_map(game, game->map->height - 1);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->img)
	{
		mlx_destroy_image(game->mlx, game->img->mlx_img);
		free(game->img);
	}
	if (game->error_msg)
		ft_free_tab((void **)game->error_msg);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

char	**ft_init_error_messages(void)
{
	char	**arr;
	int		i;

	arr = (char **)ft_calloc(12, sizeof(char *));
	if (!arr)
		return (NULL);
	arr[NO_FILE] = ft_strdup("bad file: please add an file with .cub extension\n");
	arr[TOO_MANY_FILE] = ft_strdup("bad file: too many files, please use only one\n");
	arr[BAD_EXTENSION] = ft_strdup("bad extension file: filename need .cub extension\n");
	arr[BAD_FORMAT] = ft_strdup("bad filename: please use a valid filename\n");
	arr[NOT_FOUND] = ft_strdup("bad filename: file not found\n");
	arr[INVALID_SYNTAX] = ft_strdup(": use or redifine of an invalide syntax\n");
	arr[INVALID_CHAR] = ft_strdup(": use of an invalid char on map\n");
	arr[MULTI_SPAWN] = ft_strdup(": redifine of spawn, please use only one\n");
	arr[NO_SPAWN] = ft_strdup("error in file: no spawn in map\n");
	arr[COPY_ERROR] = ft_strdup("error during the copy of the map\n");
	arr[INVALID_HEADER] = ft_strdup("error in file: invalid line in head\n");
	i = -1;
	while (++i < 11)
		if (!arr[i])
			return (ft_free_tab((void **)arr), NULL);
	return (arr);
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
	game->player = ft_init_player(game);
	game->error_msg = ft_init_error_messages();
	game->plane = ft_init_vector(1, 0);
	if (!game->map || !game->textures_path || !game->player || !game->plane
		|| !game->error_msg || !ft_parsing(game, ac, av))
		return (ft_free_all(game), NULL);
	ft_update_player(game);
	game->assets = ft_init_assets(game, game->mlx);
	game->ray = ft_init_ray();
	game->img = ft_init_img(game->mlx, NULL, S_WIDTH, S_HEIGHT);
	game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "cub3d");
	if  (!game->assets || !game->ray || !game->img || !game->win)
		return (ft_free_all(game), NULL);
	return (game);
}
