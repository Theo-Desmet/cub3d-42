/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:13:55 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/08 16:57:52 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ************************************************************************** */
/*                                atorgb                                      */
/* ************************************************************************** */

int		ft_check_is_rgb(char *line, char *str);
int		ft_atorgb(char *str);

/* ************************************************************************** */
/*                              check_border                                  */
/* ************************************************************************** */

int		ft_check_is_a_border(t_data *data, int **map, int x, int y);
int		ft_is_line_bordere(t_data *data, int *line);
int		ft_check_border(t_data *data, int **map);

/* ************************************************************************** */
/*                               check_map                                    */
/* ************************************************************************** */

int		ft_check_map(t_data *data, char *line, t_check *check);
int		ft_is_valid_map_line(t_data *data, char *line);
int		ft_check_spawn(char *line, int spawn);
t_check	*ft_init_check(t_check *check);
int		ft_check_file(t_data *data, int fd, t_check *check);

/* ************************************************************************** */
/*                            check_map_head                                  */
/* ************************************************************************** */

int		ft_check_map_head(t_data *data, char *line, t_check *check);
int		ft_check_is_head(char *str);
int		ft_check_valid_head(t_data *data, t_check *check);

/* ************************************************************************** */
/*                               fill_map                                     */
/* ************************************************************************** */

int		*ft_fill_line(t_data *data, char *line, int *map);
int		**ft_fill_map(t_data *data, int **map, char *line, int fd);
int		ft_copy_map(t_data *data, int **map, char *path);

/* ************************************************************************** */
/*                               parsing                                      */
/* ************************************************************************** */

int		ft_check_valid_path(const char *line, const char *str);
char	*ft_getpath(char *line);
int		ft_check_ext_file(char *str, char *ext);
int		ft_parsing(t_data *data, char **argv);

#endif
