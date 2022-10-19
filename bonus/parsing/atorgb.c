/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atorgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 08:19:09 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/19 08:32:53 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*ft_get_argb(const char *line, int *j, int i)
{
	char	*dup;

	dup = ft_strdup(&line[i]);
	if (!dup)
		return (NULL);
	while (dup[*j] && ft_isdigit(dup[*j]))
		*j += 1;
	dup[*j] = 0;
	if (ft_strlen(dup) <= 3)
		return (dup);
	return (NULL);
}

static int	ft_get_nbrgb(const char *line, int *shift, int *i, int rgb)
{
	char	*dup;
	int		nb;
	int		j;

	j = 0;
	dup = ft_get_argb(line, &j, *i);
	if (!dup)
		return (-1);
	nb = ft_atoi(dup);
	if (nb > 255 || nb < 0)
		return (free(dup), -1);
	rgb += nb << *shift;
	if (*shift == 16)
		*shift = 8;
	else if (*shift == 8)
		*shift = 0;
	else
		*shift = -1;
	*i += j;
	free(dup);
	return (rgb);
}

static int	ft_pass_sep(char *str, int *temp)
{
	int	i;

	i = *temp;
	if (str[i] && str[i++] != ',')
		return (0);
	while (str[i] && ft_isspace(str[i]) && str[i] != '\n')
		i++;
	if (!str[i] || (!ft_isdigit(str[i]) && ft_isspace(str[i]) && str[i] != ','))
		return (0);
	*temp = i;
	return (1);
}

int	ft_check_is_rgb(char *line, char c, int *check)
{
	int	i;
	int	rgb;

	i = 0;
	while (line[i] && ft_isspace(line[i]) && line[i] != '\n')
		i++;
	if (line[i] != c)
		return (0);
	i++;
	while (line[i] && ft_isspace(line[i]) && line[i] != '\n')
		i++;
	if (!line[i])
		return (0);
	rgb = ft_atorgb(&line[i]);
	if (rgb == -1)
		return (0);
	*check = 1;
	return (rgb);
}

int	ft_atorgb(char *str)
{
	int	rgb;
	int	i;
	int	shift;

	i = 0;
	shift = 16;
	rgb = 0;
	while (str[i])
	{
		rgb = ft_get_nbrgb(str, &shift, &i, rgb);
		if (rgb < 0)
			return (-1);
		while (str[i] && ft_isspace(str[i]) && str[i] != '\n')
			i++;
		if (shift == -1)
			break ;
		if (!ft_pass_sep(str, &i))
			return (-1);
	}
	if (str[i] != '\n')
		return (-1);
	return (rgb);
}
