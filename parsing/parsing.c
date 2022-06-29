/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:49:15 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/29 10:40:56 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_valid_path(char *line, char *str)
{
	int	i;

	i = 2;
	if (ft_strncmp(line, str, 3))
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || (line[i] != '.' && line[i] != '/'))
		return (0);
	return (1);
}

t_img	*ft_init_img(void *mlx, char *path, int area[2])
{
	int		size;
	t_img	*img;

	size = SPRITE_SIZE;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	if (path)
	{
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size, &size);
		free(path);
	}
	else
		img->mlx_img = mlx_new_image(mlx, area[0], area[1]);
	if (!img->mlx_img)
		return (NULL);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		return (NULL);
	return (img);
}

int	ft_atorgb(char *str)
{
	char	*temp;
	int	rtn;
	int	i;
	int	j;
	int	shift;

	i = 0;
	shift = 16;
	rtn = 0;
	while (str[i])
	{
		j = 0;
		temp = ft_strdup(&str[i]);
		while (temp[j] && ft_isdigit(temp[j]))
			j++;
		temp[j] = 0;
		if (ft_strlen(temp) <=3 && ft_atoi(temp) < 256)
		{
			rtn += ft_atoi(temp) << shift;
			if (shift == 16)
				shift = 8;
			else if (shift ==8)
				shift = 0;
			else
				shift = -1;
		}
		free(temp);
		i += j;
		while (str[i] && str[i] == ' ')
			i++;
		if (shift == -1)
			break;
		if (str[i] && str[i++] != ',')
			return (-1);
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i] || (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ','))
			return (-1);
	}
	if (str[i] != '\n')
		return (-1);
	return (rtn);
}

int	ft_check_is_rgb(char *line, char *str)
{
	int	i;
	int	rgb;

	i = 1;
	if (ft_strncmp(line, str, 2))
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	rgb = ft_atorgb(&line[i]);
	if (rgb == -1)
		return (0);
	return (rgb);
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

int	ft_check_map_head(t_data *data, char *line, t_check *check)
{
	if (*line == '\n')
		return (-1);
	else if (ft_check_valid_path(line, "EA ") && !check->east)
		check->east = 1;
	else if (ft_check_valid_path(line, "WE ") && !check->weast)
		check->weast = 1;
	else if (ft_check_valid_path(line, "NO ") && !check->north)
		check->north = 1;
	else if (ft_check_valid_path(line, "SO ") && !check->south)
		check->south = 1;
	else if (ft_check_is_rgb(line, "F ") && !check->south)
	{
		data->assets->floor = ft_check_is_rgb(line, "F ");
		check->floor = 1;
	}
	else if (ft_check_is_rgb(line, "C ") && !check->south)
	{
		data->assets->ceiling = ft_check_is_rgb(line, "C ");
		check->ceiling = 1;
	}
	return (-2);
}

int	ft_check_is_head(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!ft_strncmp(&str[i], "EA ", 3)
			|| !ft_strncmp(&str[i], "WE ", 3)
			|| !ft_strncmp(&str[i], "NO ", 3)
			|| !ft_strncmp(&str[i], "SO ", 3)
			|| !ft_strncmp(&str[i], "F ", 2)
			|| !ft_strncmp(&str[i], "C ", 2)
			|| str[i] == '\n')
		return (1);
	return (0);
}

int     ft_check_ext_file(char *str, char *ext)
{
	int     i;
	int     fd;

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

int	ft_is_valid_map_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] != '1' && line[i] != '\n')
			return (0);
		while (line[i] == '1')
			i++;
		while (line[i] == '0'
				|| line[i] == 'W' || line[i] == 'E'
				|| line[i] == 'S' || line[i] == 'N')
			i++;
		if (!line[i] || line[i] == '\n')
		{
			if (i > data->map->width)
				data->map->width = i;
			return (i + 1);
		}
	}
	return (0);
}

int	ft_check_spawn(char *line, int spawn)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'W' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'N')
		{
			if (!spawn)
				spawn++;
			else if (spawn)
				return (-1);
		}
		i++;
	}
	return (spawn);
}

int	ft_check_valid_head(t_data *data, t_check *check)
{
	if (!check->east || !check->weast || !check->north
		|| !check->south || !check->floor || !check->ceiling)
		return (0);
	return (1);
}

t_check	*ft_init_check(t_check *check)
{
	check->east = 0;
	check->weast = 0;
	check->north = 0;
	check->south = 0;
	check->floor = 0;
	check->ceiling = 0;
	check->spwan = 0;
	return (check);
}

int	ft_do_check_map_head(t_data *data, char *line, t_check *check)
{
	int	temp;

	temp = ft_check_map_head(data, line, check);
	free(line);
	if (temp < -1)
		return (0);
	return (1);
}

int	ft_check_map(t_data *data, char *line, t_check *check)
{
	if (!ft_check_valid_head(data, check))
	{
		free(line);
		return (0);
	}
	if (!ft_is_valid_map_line(data, line))
	{
		free(line);
		return (0);
	}
	check->spwan = ft_check_spawn(line, check->spwan);
	if (check->spwan < 0)
	{
		free(line);
		return (0);
	}
	data->map->height++;
	return (1);
}

int	ft_check_file(t_data *data, int fd, t_check *check)
{
	char	*line;
	int		ishead;

	check = ft_init_check(check);
	ishead = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (ishead && !ft_check_is_head(line))
			ishead = 0;
		if (ishead && !ft_do_check_map_head(data, line, check))
			return (0);//add msg error
		if (!ishead && !ft_check_map(data, line, check))
			return (0);//add msg error
		free(line);
	}
	if (!check->spwan)
		return (0);
	free(check);
	return (1);
}

int	*ft_fill_line(t_data *data, char *line, int *map)
{
	int	y;

	y = 0;
	while (y < data->map->width)
	{
		if (!line[y] || line[y] == '\n')
			while (y < data->map->width)
				map[y++] = -1;
		else if (line[y] == ' ')
			map[y] = -1;
		else if (line[y] == 'W' || line[y] == 'E'
			|| line[y] == 'N' || line[y] == 'S')
			map[y] = line[y];
		else
			map[y] = line[y] - '0';
		y++;
	}
	return (map);
}

int	**ft_fill_map(t_data *data, int **map, char *line, int fd)
{
	int	x;

	x = 0;
	while (x < data->map->height)
	{
		map[x] = malloc(sizeof(int) * data->map->width);
		if (!map[x])
			return (ft_free_map(data, x - 1), NULL);
		map[x] = ft_fill_line(data, line, map[x]);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		x++;
	}
	return (map);
}

int	ft_copy_map(t_data *data, int **map, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (0);
	line = get_next_line(fd);
	while (ft_check_is_head(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	map = ft_fill_map(data, map, line, fd);
	if (!map)
		return (0);
	return (1);
}

int	ft_is_line_bordere(t_data *data, int *line)
{
	int	i;

	i = 0;
	while (i < data->map->width)
	{
		while (i <= data->map->width && line[i] == -1)
			i++;
		while (i <= data->map->width && line[i] == 1)
			i++;
		if (i == data->map->width)
			return (1);
		if (line[i] != 1 && line[i] != -1)
			return (0);
	}
	return (1);
}

int	ft_check_is_a_border(t_data *data, int **map, int x, int y)
{
	if (y != 0 && map[x - 1][y - 1] == -1)
		return (0);
	if (map[x - 1][y] == -1)
		return (0);
	if (y < data->map->height && map[x - 1][y + 1] == -1)
		return (0);
	if (y != 0 && map[x][y - 1] == -1)
		return (0);
	if (y < data->map->height && map[x][y + 1] == -1)
		return (0);
	if (y != 0 && map[x + 1][y - 1] == -1)
		return (0);
	if (map[x + 1][y] == -1)
		return (0);
	if (y < data->map->height && map[x + 1][y + 1] == -1)
		return (0);
	return (1);
}

int	ft_check_border(t_data *data, int **map)
{
	int	x;
	int	y;

	x = 1;
	if (!ft_is_line_bordere(data, map[0]))
		return (printf("ERROR: l.1"), 0);
	while (x < data->map->height - 1)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (map[x][y] != 1 && map[x][y] != -1)
				if (!ft_check_is_a_border(data, map, x, y))
					return (printf("ERROR: l.%d c%d", x, y), 0);
			y++;
		}
		x++;
	}
	if (!ft_is_line_bordere(data, map[data->map->height - 1]))
		return (printf("ERROR: l.1"), 0);
	return (1);
}

int	ft_parsing(t_data *data, char **argv)
{
	int		fd;
	t_check *check;

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
