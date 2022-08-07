/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:41:49 by bbordere          #+#    #+#             */
/*   Updated: 2022/07/25 14:41:44 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

inline void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || ft_get_pixel(img, x, y) == color)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

inline unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	unsigned int	color;
	char			*pix;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pix;
	return (color);
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
