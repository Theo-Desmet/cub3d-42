/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:49:15 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/17 18:18:16 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

size_t	ft_get_texture_index(const char *id)
{
	if (!ft_strcmp(id, "EA"))
		return (0);
	if (!ft_strcmp(id, "WE"))
		return (1);
	if (!ft_strcmp(id, "NO"))
		return (2);
	return (3);
}

int	ft_check_valid_path(t_game *game, const char *line, const char *str)
{
	int	i;
	int	temp;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strncmp(&line[i], str, 2))
		return (0);
	i += 2;
	temp = i;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (temp == i)
		return (0);
	game->textures_path[ft_get_texture_index(str)] = ft_getpath(&line[i]);
	return (1);
}

char	*ft_getpath(const char *line)
{
	int		i;
	char	*path;

	path = ft_strdup(line);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && !ft_isspace(path[i]))
		i++;
	path[i] = 0;
	return (path);
}

int	ft_check_ext_file(t_game *game, char *str, char *ext)
{
	int	i;
	int	fd;

	i = 0;
	while (str[i])
		i++;
	if (ft_strncmp(&str[i - ft_strlen(ext)], ext, ft_strlen(ext)))
		return (ft_err_file_name(game, 2, BAD_EXTENSION), 0);
	i -= ft_strlen(ext) + 1;
	if (str[i] == '/')
		return (ft_err_file_name(game, 2, BAD_FORMAT), 0);
	fd = open (str, O_RDONLY);
	if (fd == -1)
		return (ft_err_file_name(game, 2, NOT_FOUND), 0);
	return (fd);
}

int	ft_parsing(t_game *game, int argc, char **argv)
{
	int		fd;
	t_check	*check;

	if (argc != 2)
		return (ft_err_file_name(game, argc, 0), 0);
	fd = ft_check_ext_file(game, argv[1], ".cub");
	if (!fd)
		return (0);
	check = malloc(sizeof(t_check));
	if (!check)
		return (0);
	if (!ft_check_file(game, fd, check))
		return (free(check), 0);
	close(fd);
	free(check);
	game->map->map = ft_calloc(game->map->height, sizeof(int *));
	if (!game->map->map)
		return (0);
	if (!ft_copy_map(game, game->map->map, argv[1]))
		return (0);
	if (!ft_check_border(game, game->map->map))
		return (0);
	return (1);
}
