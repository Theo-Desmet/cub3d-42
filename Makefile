# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 08:53:24 by tdesmet           #+#    #+#              #
#    Updated: 2022/10/20 00:11:38 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

CFLAGS = -I includes/ -Ofast -flto -Wall -Werror -Wextra

#CFLAGS = -I includes/ -O0 -Wall -Werror -Wextra

FILES = src/raycasting/floor.c\
	src/raycasting/ray.c\
	src/raycasting/raycasting.c\
	src/parsing/atorgb.c\
	src/parsing/check_map.c\
	src/parsing/check_map_head.c\
	src/parsing/check_border.c\
	src/parsing/fill_map.c\
	src/parsing/err_parsing.c\
	src/parsing/parsing.c\
	src/cleaning.c\
	src/drawing.c\
	src/init2.c\
	src/init.c\
	src/key.c\
	src/main.c\
	src/move.c\
	src/utils.c\

BFILES = bonus/cleaning2.c\
	 bonus/door.c\
	 bonus/drawing.c\
	 bonus/init2.c\
	 bonus/init.c\
	 bonus/main.c\
	 bonus/move.c\
	 bonus/cleaning.c\
	 bonus/door_utils.c\
	 bonus/drawing_utils.c\
	 bonus/init3.c\
	 bonus/key.c\
	 bonus/minimap.c\
	 bonus/objects.c\
	 bonus/raycasting/floor.c\
	 bonus/raycasting/raycasting.c\
	 bonus/raycasting/utils_raycasting.c\
	 bonus/raycasting/ray.c\
	 bonus/raycasting/sprite.c\
	 bonus/raycasting/utils_render.c\
	 bonus/parsing/atorgb.c\
	 bonus/parsing/check_map.c\
	 bonus/parsing/err_parsing.c\
	 bonus/parsing/parsing.c\
	 bonus/parsing/check_border.c\
	 bonus/parsing/check_map_head.c\
       	 bonus/parsing/fill_map.c\
	 bonus/enemy/init_enemy.c\
	 bonus/enemy/move_enemy.c\
	 bonus/enemy/pathfinding.c\
	 bonus/enemy/random.c\
	 bonus/enemy/utils_enemy.c\

OBJS = $(FILES:.c=.o)

BOBJS = $(BFILES:.c=.o)

NAME = cub3d

DEPS =	includes/cub3d.h\
		includes/define.h\
		includes/enemy.h\
		includes/parsing.h\
		includes/struct.h\
		Makefile

BDEPS =	includes/cub3d_bonus.h\
		includes/define.h\
		includes/enemy.h\
		includes/parsing.h\
		includes/struct.h\
		Makefile

BNAME = cub3d_bonus

%.o: %.c
	@printf "\033[0;33mCompiling file: %-33.33s\r" $@
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

$(NAME): $(OBJS)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	@ $(CC) $(CFLAGS) $(OBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o  $(NAME) 

all: $(NAME)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	@ $(CC) $(CFLAGS) $(OBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(NAME)

bonus: $(BOBJS) $(BDEPS)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	@ $(CC) $(CFLAGS) $(BOBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(BNAME)

clean:
	@ rm -f $(OBJS)
	@ rm -f $(BOBJS)
	@ $(MAKE) -C libft clean --no-print-directory
	@ $(MAKE) -C mlx_linux/ clean --no-print-directory
	@ printf '\033[0;32mclean done\033[0m\n'

fclean: clean
	@ rm -f $(NAME)
	@ rm -f $(BNAME)
	@ $(MAKE) -C libft fclean --no-print-directory
	@ printf '\033[0;32mfclean done\033[0m\n'

re: fclean $(NAME)

re_bonus: fclean bonus

.PHONY: all clean fclean re

.SILENT: $(OBJS)
