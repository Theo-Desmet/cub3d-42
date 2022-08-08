/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:49:15 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/08 14:55:33 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	ft_check_ext_file(char *str, char *ext)
{
	int	i;
	int	fd;

	i = 0;
	while (str[i])
		i++;
	if (ft_strncmp(&str[i - ft_strlen(ext)], ext, ft_strlen(ext)))
		return (ft_putstr_fd("bad extension file: need .cub\n", 2), 0);
	i -= ft_strlen(ext) + 1;
	if (str[i] == '/')
		return (ft_putstr_fd("bad extension file: need .cub\n", 2), 0);
	fd = open (str, O_RDONLY);
	if (fd == -1)
		return (perror(""), 0);
	return (fd);
}

int	ft_parsing(t_data *data, char **argv)
{
	int		fd;
	t_check	*check;

	fd = ft_check_ext_file(argv[1], ".cub");
	if (!fd)
		return (0);
	check = malloc(sizeof(t_check));
	if (!check)
		return (0);
	if (!ft_check_file(data, fd, check))
		return (free(check), 0);
	close(fd);
	data->map->map = malloc(sizeof(int *) * data->map->height);
	if (!ft_copy_map(data, data->map->map, argv[1]))
		return (0);
	if (!ft_check_border(data, data->map->map))
		return (0);
	return (printf("YYYYEEEEESSSS\n"), 1);
}
