/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:49:15 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/12 15:22:04 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_check_valid_path(const char *line, const char *str)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], str, 3))
		return (0);
	i += 2;
	while (line[i] && line[i] == ' ')
		i++;
	return (1);
}

char	*ft_getpath(char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	path = ft_strdup(&line[i]);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && path[i] != '\n')
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
		return (ft_err_file_name(game, 2, 1), 0);
	i -= ft_strlen(ext) + 1;
	if (str[i] == '/')
		return (ft_err_file_name(game, 2, 2), 0);
	fd = open (str, O_RDONLY);
	if (fd == -1)
		return (ft_err_file_name(game, 2, 3), 0);
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
		return (ft_free_game(game), 0);
	if (!ft_check_file(game, fd, check))
		return (ft_free_game(game), free(check), 0);
	close(fd);
	free(check);
	game->map->map = malloc(sizeof(int *) * game->map->height);
	if (!game->map->map)
		return (ft_free_game(game), 0);
	if (!ft_copy_map(game, game->map->map, argv[1]))
		return (ft_free_game(game), 0);
	if (!ft_check_border(game, game->map->map))
		return (ft_free_game(game), 0);
	return (printf("YYYYEEEEESSSS\n"), 1);
}