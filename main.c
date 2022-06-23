/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:06:07 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/15 15:00:28 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*ft_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->assets = malloc(sizeof(t_assets));
	if (!data->assets)
		return (NULL);//leak
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (NULL);//leak
	data->map->width = 0;
	data->map->height = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (NULL);//leak
	data->sprite_size = SPRITE_SIZE;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (1);//invalid nb arg
	data = ft_init();
	if (!data)
		return (1);
	ft_parsing(data, argv);
	return (0);
}
