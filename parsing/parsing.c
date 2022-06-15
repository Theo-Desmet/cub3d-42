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
	if (!line[i] || line[i] != '.' || (line[i] && line[i + 1] != '/'))
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
		img->mlx_img = mlx_new_image(mlx, SPRITE_SIZE * width,
				SPRITE_SIZE * height);//pas utilisé
	if (!img->mlx_img)
		return (NULL);//leak
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
	int	shift;

	i = 0;
	shift = 16;
	rtn = 0;
	while (str[i])
	{
		temp = ft_strdup(&str[i]);
		while (temp[i] && ft_isdigit(temp[i]))
			i++;
		temp[i] = 0;
		if (ft_strlen(temp) <=3 && ft_atoi(temp) < 256)
		{
			rtn += ft_atoi(temp) << shift;
			if (shift == 16)
				shift = 8;
			else
				shift = 0;
		}
		free(temp);
		if (shift == 0)
			break ;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i++] != ',')
			return (-1);
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i] || (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ','))
			return (-1);
	}
	if (str[i])
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

int	ft_check_map_head_cond(t_data *data, char *line, int check[])
{
	if (ft_check_valid_path(line, "EA ") && !check[0])
	{
		data->assets->w_east = ft_init_img(data->mlx, ft_strchr(line, '.'), 0, 0);
		return (0);
	}
	else if (ft_check_valid_path(line, "WE ") && !check[1])
	{
		data->assets->w_weast = ft_init_img(data->mlx, ft_strchr(line, '.'), 0, 0);
		return (1);
	}
	else if (ft_check_valid_path(line, "NO ") && !check[2])
	{
		data->assets->w_north = ft_init_img(data->mlx, ft_strchr(line, '.'), 0, 0);
		return (2);
	}
	else if (ft_check_valid_path(line, "SO ") && !check[3])
	{
		data->assets->w_south = ft_init_img(data->mlx, ft_strchr(line, '.'), 0, 0);
		return (3);
	}
	else if (ft_check_is_rgb(line, "F ") && !check[4])
	{
		data->assets->floor = ft_check_is_rgb(line, "F ");
		return (4);
	}
	else if (ft_check_is_rgb(line, "C ") && !check[5])
	{
		data->assets->floor = ft_check_is_rgb(line, "C ");
		return (5);
	}
	return (-1);
}

int	ft_check_map_head(t_data *data, int fd)
{
	char	*line;
	int	check[6];
	int	i;

	check[0] = 0;
	check[1] = 0;
	check[2] = 0;
	check[3] = 0;
	check[4] = 0;
	check[5] = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (*line != '\n')
		{
			i = ft_check_map_head_cond(data, line, check);
			check[i] = 1;
		}
		free(line);
	}
	return (1);
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

int	ft_parsing(t_data *data, char **argv)
{
	int	fd;

	fd = ft_check_ext_file(argv[1], ".cub");
	if (!fd)
		return (0);
	ft_check_map_head(data, fd);
	return (1);
}
