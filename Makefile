# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 08:53:24 by tdesmet           #+#    #+#              #
#    Updated: 2022/10/17 19:05:35 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -I includes/ -Ofast -flto -g3 -Wall -Werror -Wextra

CFLAGS = -I includes/ -O0 -g3 -Wall -Werror -Wextra

FILES = $(wildcard src/*.c) $(wildcard src/raycasting/*.c) $(wildcard src/parsing/*.c)

BFILES = $(wildcard bonus/*.c) $(wildcard bonus/raycasting/*.c) $(wildcard bonus/parsing/*.c) $(wildcard bonus/enemy/*.c)

OBJS = $(FILES:.c=.o)

BOBJS = $(BFILES:.c=.o)

NAME = cub3d

DEPS = $(wildcard includes/*.h) Makefile

BNAME = cub3d_bonus

%.o: %.c $(DEPS)
	@printf "\033[0;33mCompiling file: %-33.33s\r" $@
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -D BONUS=1 -c $< -o $@

$(NAME): $(OBJS)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	@ $(CC) $(CFLAGS) $(OBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o  $(NAME) 

all: $(NAME)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	@ $(CC) $(CFLAGS) $(OBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(NAME)

malloc_test: $(OBJS) $(DEPS)	
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -L. -lmallocator

bonus: $(BOBJS) $(DEPS)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	@ $(CC) $(CFLAGS) $(BOBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(BNAME)

clean:
	@ rm -f $(OBJS)
	@ rm -f $(BOBJS)
	@ $(MAKE) -C libft clean --no-print-directory
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
