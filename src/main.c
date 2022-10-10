/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:20:28 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/10 11:16:28 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// # include <sys/time.h>

// unsigned long	ft_get_time(void)
// {
// 	struct timeval	t;

// 	gettimeofday(&t, NULL);
// 	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
// }

// void	ft_fps(t_game *game)
// {
// 	static	unsigned long	cur;
// 	static	int				frames;
// 	static	char			*fps;

// 	if (!cur)
// 		cur = ft_get_time() + 1000;
// 	if (cur <= ft_get_time())
// 	{
// 		cur = ft_get_time() + 1000;
// 		if (fps)
// 			free(fps);
// 		fps = ft_itoa(frames);
// 		frames = 0;
// 	}
// 	if (fps)
// 		mlx_string_put(game->mlx, game->win, S_WIDTH - 50, 10, 0xFF0000, fps);
// 	frames++;
// }

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_init_game(ac, av);
	if (!game)
		exit(EXIT_FAILURE);
	mlx_hook(game->win, 2, 1L, ft_key_down, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_up, game);
	mlx_hook(game->win, 17, 1L, ft_free_all, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	ft_free_all(game);
	return (0);
}
