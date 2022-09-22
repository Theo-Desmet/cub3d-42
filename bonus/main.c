/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:16:13 by bbordere          #+#    #+#             */
/*   Updated: 2022/09/22 16:34:41 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_parsing(t_game *game, int argc, char **argv);

int	mouse_handling(int x, int y, t_game *game)
{
	static int	last_x;
	
	(void)y;
	mlx_mouse_move(game->mlx, game->win, screenWidth / 2, screenHeight / 2);
	if (last_x != x)
	{
		if (last_x > x)
		{
			game->mouse_right = false;
			game->mouse_left = true;
		}
		else if (last_x < x)
		{
			game->mouse_left = false;
			game->mouse_right = true;
		}
		last_x = x;
	}
	else
	{
		game->mouse_left = false;
		game->mouse_right = false;
	}
	return (1);
}

# include <sys/time.h>

unsigned long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_fps(t_game *game)
{
	static	unsigned long	last;
	static	unsigned long	cur;
	static	int				frames;
	static	char			*fps;


	last = ft_get_time();
	if (!cur)
		cur = ft_get_time() + 1000;
	if (cur <= ft_get_time())
	{
		cur = ft_get_time() + 1000;
		if (fps)
			free(fps);
		fps = ft_itoa(frames);
		frames = 0;
	}
	if (fps)
		mlx_string_put(game->mlx, game->win, screenWidth - 50, 10, 0xFF0000, fps);
	frames++;
}


int main(int ac, char **av)
{
	t_game	*game;

	game = ft_init_game(ac, av);
	if (!game)
		exit(EXIT_FAILURE);
	// mlx_mouse_hide(game->mlx, game->win);
	mlx_do_sync(game->mlx);
	mlx_hook(game->win, 2, 1L, ft_key_down, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_up, game);
	mlx_hook(game->win, 17, 1L, ft_free_all, game);
	// mlx_hook(game->win, 6, 1L << 6, mouse_handling, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	ft_free_all(game);
	return (0);
}