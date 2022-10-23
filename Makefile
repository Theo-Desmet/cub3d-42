# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 08:53:24 by tdesmet           #+#    #+#              #
#    Updated: 2022/10/23 23:11:57 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

CFLAGS = -I includes/ -Wall -Werror -Wextra

FILES = 	src/raycasting/floor.c\
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

BFILES =	bonus/cleaning2.c\
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

DEPS =		includes/define.h\
			includes/enemy.h\
			includes/parsing.h\
			includes/struct.h\
			Makefile

OBJS = $(FILES:.c=.o)

BOBJS = $(BFILES:.c=.o)

NAME = cub3D

BNAME = cub3D_bonus

ifeq ($(MAKECMDGOALS), bonus)
	CFLAGS+= -Ofast -flto
	DEPS += includes/cub3d_bonus.h
else ifeq ($(MAKECMDGOALS), re_bonus)
	CFLAGS+= -Ofast -flto
	DEPS += includes/cub3d_bonus.h
else
	DEPS += includes/cub3d.h
endif

%.o: %.c $(DEPS)
	@printf "\033[0;33mCompiling file: %-33.33s\r" $@
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

$(NAME): $(OBJS) 
	@ $(MAKE) -C libft all --no-print-directory -s
	@ $(MAKE) -C mlx_linux/ all -s
	@ $(CC) $(CFLAGS) $(OBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(NAME) 
	@ printf '\033[0;32mcompilation done\033[0m\n'

all: $(NAME)
	@ $(MAKE) -C libft all --no-print-directory -s
	@ $(MAKE) -C mlx_linux/ all -s
	@ $(CC) $(CFLAGS) $(OBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(NAME)
	@ printf '\033[0;32mcompilation done\033[0m\n'

bonus: $(BDEPS) $(BOBJS)
	@ $(MAKE) -C libft all --no-print-directory -s
	@ $(MAKE) -C mlx_linux/ all -s
	@ $(CC) $(CFLAGS) $(BOBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(BNAME)
	@ printf '\033[0;32mcompilation done\033[0m\n'

clean:
	@ rm -f $(OBJS)
	@ rm -f $(BOBJS)
	@ $(MAKE) -C libft clean --no-print-directory -s
	@ $(MAKE) -C mlx_linux/ clean --no-print-directory -s
	@ printf '\033[0;32mclean done\033[0m\n'

fclean: clean
	@ rm -f $(NAME)
	@ rm -f $(BNAME)
	@ $(MAKE) -C libft fclean --no-print-directory
	@ printf '\033[0;32mfclean done\033[0m\n'

re: fclean $(NAME)

re_bonus: fclean bonus

.PHONY: all clean fclean re

.SILENT: $(OBJS) $(MAKE)
