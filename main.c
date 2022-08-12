/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:06:07 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/10 08:43:10 by tdesmet          ###   ########.fr       */
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

void    ft_free_map(t_data *data, int i)
{
        while (i >= 0)
        {
                free(data->map->map[i]);
                i--;
        }
        free(data->map->map);
        free(data->map);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_init();
	if (!data)
		return (1);
	if (!ft_parsing(data, argc, argv))
		return (0);
	ft_free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}
