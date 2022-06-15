/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:55:51 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/15 17:33:02 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	unsigned int	color;
	char			*pix;

	pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pix;
	return (color);
}

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

#define SIZE 1

void	ft_put_square(t_img *img, int x, int y, int color)
{
	int	size;
	size_t	i;
	size_t	j;

	size = SIZE;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			ft_put_pixel(img, x + i, y + j, color);
			i++;
		}
		j++;
	}

}

#include <math.h>

void	ft_dda(t_img *img, double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;
	double	step;
	int		x;
	int		y;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	step = (dx >= dy) ? dx : dy;
	x = x1;
	y = y1;

	int i = 0;
	while (i < step)
	{
		ft_put_pixel(img, x, y, 0x00FF0000);
		x += dx;
		y += dy;
		i++;
	}	
}

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;


#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// void	ft_draw_line(t_img *img, int x, int y, int len, int color)
// {
// 	int	i;

// 	i = 0;
// 	while (i <= len)
// 	{
// 		// ft_put_square(img, x, y + i, color);
// 		ft_put_pixel(img, x, y + i, color);
// 		i++;
// 	}
// }

double	ft_conversion(double angle)
{
	return (angle * 3.14159265358979323846 / 180);
}

void *mlx;
void	*mlx_win;

void	ft_draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	double	dx;
	double	dy;
	int		pixels;

	dx = x2 - x1;
	dy = y2 - y1;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= dy;
	int	x;
	int	y;

	x = x1;
	y = y1;
	while (pixels)
	{
		mlx_pixel_put(mlx, mlx_win, x, y, color);
		// ft_put_pixel(img, x, y, color);
		x += dx;
		y += dy;
		pixels--;
	}
	
}

int	ft_key_hook(int keycode, double *player_angle)
{

	if (keycode == 'd' || keycode == 65363)
	{*player_angle += 5;printf("TEST\n");}
	else if (keycode == 'a' || keycode == 65361)
		*player_angle -= 5;
	return (0);
}

int	main(void)
{
	
	t_img	img;


	

	#define RED 0xFF0000
	#define GREEN 0x008000
	#define PURPLE 0x800080
	#define GREY 0x6D6D6D


	t_vector	player;
	t_vector	ray;
	double		fov = 60;

	mlx = mlx_init();
	player.x = 15;
	player.y = 20;

	double player_angle = 180;

	double step = fov / screenWidth;
	double	ray_angle = player_angle - (fov / 2);


	mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "Hello world!");
	img.mlx_img = mlx_new_image(mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);

	mlx_put_image_to_window(mlx, mlx_win, img.mlx_img, 0, 0);
		
	
	for (int ray_count = 0; ray_count < screenWidth; ray_count++)
	{
		t_vector	ray;
		ray.x = player.x;
		ray.y = player.y;

		int	wall = 0;
		while (!wall)
		{
			ray.x += cos(ft_conversion(ray_angle)) / 256;
			ray.y += sin(ft_conversion(ray_angle)) / 256;
			wall = worldMap[(int)floor(ray.x)][(int)floor(ray.y)];
		}
		
		double half_height = (screenHeight / 2);
		double	distance = sqrt(pow(player.x - ray.x, 2) + pow(player.y - ray.y, 2));
		distance *= cos(ft_conversion(ray_angle - player_angle));
		double	wall_height = floor(half_height / distance);
		ft_draw_line(&img, ray_count, 0, ray_count, half_height - wall_height, GREY);
		ft_draw_line(&img, ray_count, half_height - wall_height, ray_count, half_height + wall_height, RED);
		ft_draw_line(&img, ray_count, half_height + wall_height, ray_count, screenHeight, GREEN);

		ray_angle += step;
	}
	mlx_hook(mlx_win, 2, 1L, exit, EXIT_FAILURE);
	mlx_loop(mlx);
}
