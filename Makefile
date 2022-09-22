# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 08:53:24 by tdesmet           #+#    #+#              #
#    Updated: 2022/09/22 16:34:52 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

CFLAGS = -I includes/ -Ofast -finline-functions -fno-rtti -flto -g3 #-Wall -Werror -Wextra

# CFLAGS = -I includes/ -O0#-Wall -Werror -Wextra

BFLAG = 

FILES = $(wildcard src/*.c) $(wildcard src/raycasting/*.c) $(wildcard src/parsing/*.c)

BFILES = $(wildcard bonus/*.c) $(wildcard bonus/raycasting/*.c) $(wildcard bonus/parsing/*.c)

OBJS = $(FILES:.c=.o)

BOBJS = $(BFILES:.c=.o)

NAME = cub3d

DEPS = $(wildcard includes/*.h)

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

bonus: $(BOBJS)
	@ $(MAKE) -C libft all --no-print-directory
	@ $(MAKE) -C mlx_linux/ all
	@ $(CC) $(CFLAGS) -D BONUS=1 $(BOBJS) libft/libft.a mlx_linux/libmlx.a -lXext -lX11 -lm -o $(BNAME)

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
