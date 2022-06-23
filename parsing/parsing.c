/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:49:15 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/15 17:33:04 by tdesmet          ###   ########.fr       */
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

t_img	*ft_init_img(void *mlx, char *path, int width, int height)
{
	t_img	*img;
	int		size;

	size = SPRITE_SIZE;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	if (path)
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size, &size);
	else
		img->mlx_img = mlx_new_image(mlx, width, height);
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

int	ft_check_map_head_cond(t_data *data, char *line, int check[])
{
	if (ft_check_valid_path(line, "EA ") && !check[0])
	{
		data->assets->w_east = ft_init_img(data->mlx, ft_getpath(line), 0, 0);
		if (!data->assets->w_east)
			return (-2);
		return (0);
	}
	else if (ft_check_valid_path(line, "WE ") && !check[1])
	{
		data->assets->w_weast = ft_init_img(data->mlx, ft_getpath(line), 0, 0);
		if (!data->assets->w_weast)
			return (-2);
		return (1);
	}
	else if (ft_check_valid_path(line, "NO ") && !check[2])
	{
		data->assets->w_north = ft_init_img(data->mlx, ft_getpath(line), 0, 0);
		if (!data->assets->w_north)
			return (-2);
		return (2);
	}
	else if (ft_check_valid_path(line, "SO ") && !check[3])
	{
		data->assets->w_south = ft_init_img(data->mlx, ft_getpath(line), 0, 0);
		if (!data->assets->w_south)
			return (-2);
		return (3);
	}
	else if (ft_check_is_rgb(line, "F ") && !check[4])
	{
		data->assets->floor = ft_check_is_rgb(line, "F ");
		return (4);//leak error
	}
	else if (ft_check_is_rgb(line, "C ") && !check[5])
	{
		data->assets->ceiling = ft_check_is_rgb(line, "C ");
		return (5);//leak error
	}
	return (-1);
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

int	ft_check_map_head(t_data *data, char *line, int check[9])
{
	int	i;

	if (*line != '\n')
	{
		i = ft_check_map_head_cond(data, line, check);
			return (i);
	}
	return (-1);
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

int	ft_check_map(t_data *data, int fd)
{
	char *line;
	int	temp;
	int	check[9];

	check[0] = 0;//EA
	check[1] = 0;//WE
	check[2] = 0;//NO
	check[3] = 0;//SO
	check[4] = 0;//F
	check[5] = 0;//C
	check[6] = 0;//spawn
	check[7] = 0;//if_head
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (ft_check_is_head(line))
		{
			temp = ft_check_map_head(data, line, check);
			if (temp < -1)
				return (0);
			if (temp == -1)
				continue;
			check[temp] = 1;
			continue ;
		}
		if (!check[0] || !check[1] || !check[2]
			|| !check[3] || !check[4] || !check[5])
			return (-1);
		if (!ft_is_valid_map_line(data, line))
			return (0);
		check[6] = ft_check_spawn(line, check[6]);
		if (check[6] < 0)
			return (0);
		data->map->height++;
	}
	if (!check[6])
		return (0);
	return (1);
}

int	ft_copy_map(t_data *data, int **map, char *str)
{
	int	x;
	int	y;
	int	fd;
	char	*line;

	x = 0;
	fd = open(str, O_RDONLY);
	if (!open)
		return (0);
	line = get_next_line(fd);
	while (ft_check_is_head(line))
		line = get_next_line(fd);
	while (x < data->map->height)
	{
		y = 0;
		map[x] = malloc(sizeof(int) * data->map->width);
		while (y < data->map->width)
		{
			if (!line[y] || line[y] == '\n')
				while (y < data->map->width)
					map[x][y++] = -1;
			else if (line[y] == ' ')
				map[x][y] = -1;
			else if (line[y] == 'W' || line[y] == 'E'
					|| line[y] == 'N' || line[y] == 'S')
				map[x][y] = line[y];
			else
				map[x][y] = line[y] - '0';
			y++;
		}
		line = get_next_line(fd);
		if (!line)
			break ;
		x++;
	}
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
		return(printf("ERROR: l.1"), 0);
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
		return(printf("ERROR: l.1"), 0);
	return (1);
}

int	ft_parsing(t_data *data, char **argv)
{
	int		fd;

	fd = ft_check_ext_file(argv[1], ".cub");
	if (!fd)
		return (0);
	if (!ft_check_map(data, fd))
		return (0);
	close(fd);
	data->map->map = malloc(sizeof(int *) * data->map->height);
	if (!ft_copy_map(data, data->map->map, argv[1]))
		return (0);
	if (!ft_check_border(data, data->map->map))
		return (0);
	return (printf("YYYYEEEEESSSS\n"), 1);
}
