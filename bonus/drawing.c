/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:41:49 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/25 11:12:22 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

inline void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height || ft_get_pixel(img, x, y) == color)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


inline unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	static	int cache_x;
	static	int	cache_y;
	static	t_img	*cache_img;
	static	unsigned int	cache_color;
	unsigned int	color;
	char			*pix;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x != cache_x || y != cache_y || img != cache_img)
	{
		pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
		color = *(unsigned int *)pix;
		cache_x = x;
		cache_y = y;
		cache_img = img;
		cache_color = color;
	}
	return (cache_color);
}

void	ft_draw_circle(t_img *img, t_vector *pos, int r, int color)
{
	double	i;
	double	angle;
	double	x;
	double	y;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x = r * cos(angle * M_PI / 180);
		y = r * sin(angle * M_PI / 180);
		ft_put_pixel(img, x + pos->x, y + pos->y, color);
		i += 0.1;
	}
	free(pos);
}

void	ft_draw_square(t_img *img, t_vector *pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			ft_put_pixel(img, (int)pos->x + i, (int)pos->y + j, color);
			j++;
		}
		i++;
	}
	free(pos);
}

void	ft_paint(t_img *element, t_img *mlx_img, t_vector *pos, int scale)
{
	int				x1;
	int				y1;
	unsigned int	color;
	int				save;

	y1 = 0;
	save = (int)pos->x;
	while (y1 < SPRITE_SIZE)
	{
		pos->x = save;
		x1 = 0;
		while (x1 < SPRITE_SIZE)
		{
			color = ft_get_pixel(element, x1, y1);
			if (!(color == (unsigned int)(0xFF << 24)))
				ft_draw_square2(mlx_img, pos, scale, color);
			pos->x += scale;
			x1++;
		}
		pos->y += scale;
		y1++;
	}
	free(pos);
}

void	ft_draw_square2(t_img *img, t_vector *pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			ft_put_pixel(img, (int)pos->x + i, (int)pos->y + j, color);
			j++;
		}
		i++;
	}
}
