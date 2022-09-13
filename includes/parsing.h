/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:13:55 by tdesmet           #+#    #+#             */
/*   Updated: 2022/09/13 11:00:47 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ************************************************************************** */
/*                                atorgb                                      */
/* ************************************************************************** */

int		ft_atorgb(char *str);
int		ft_check_is_rgb(char *line, char *str);

/* ************************************************************************** */
/*                              check_border                                  */
/* ************************************************************************** */

int		ft_check_is_a_border(t_game *game, int **map, int x, int y);
int		ft_check_border(t_game *game, int **map);

/* ************************************************************************** */
/*                               check_map                                    */
/* ************************************************************************** */

int		ft_check_map(t_game *game, char *line, t_check *check, int line_cnt);
int		ft_is_valid_map_line(t_game *game, char *line);
int		ft_check_spawn(t_game *game, char *line, int spawn, int line_cnt);
t_check	*ft_init_check(t_check *check);
int		ft_check_file(t_game *game, int fd, t_check *check);

/* ************************************************************************** */
/*                            check_map_head                                  */
/* ************************************************************************** */

int		ft_check_map_head(t_game *game, char *line, t_check *check);
int		ft_check_is_head(char *str);
int		ft_check_valid_head(t_game *game, t_check *check);

/* ************************************************************************** */
/*                               fill_map                                     */
/* ************************************************************************** */

int		*ft_fill_line(t_game *game, char *line, int *map);
int		**ft_fill_map(t_game *game, int **map, char *line, int fd);
int		ft_copy_map(t_game *game, int **map, char *path);

/* ************************************************************************** */
/*                               parsing                                      */
/* ************************************************************************** */

int		ft_check_valid_path(const char *line, const char *str);
char	*ft_getpath(char *line);
int		ft_check_ext_file(t_game *game, char *str, char *ext);
int		ft_parsing(t_game *game, int argc, char **argv);

/* ************************************************************************** */
/*                              err_parsing                                   */
/* ************************************************************************** */

void	ft_err_file_name(t_game *game, int argc, int error);
void	ft_free_game(t_game *game);
void	ft_err_in_file(t_game *game, t_check *check, int error, int line);
void	ft_err_bordere(int x, int y);
void	ft_err_copy_map(t_game *game, int nb_line);

#endif
