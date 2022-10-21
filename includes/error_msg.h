/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:46:44 by bbordere          #+#    #+#             */
/*   Updated: 2022/10/21 14:21:06 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# define NO_FILE "Error\nBad file: Please add file with '.cub' extension !\n"
# define TOO_MANY_FILES "Error\nBad file: Too many files, please use only one !\n"
# define BAD_EXT "Error\nBad file extension: File must have '.cub' extension !\n"
# define BAD_FORMAT "Error\nBad filename: Please use a valid filenam !\n"
# define NOT_FOUND "Error\nBad filename: File not found !\n"
# define INV_SYN ": Use or redefine of an invalid syntax !\n"
# define INV_CHAR ": Use of an invalid char on map !\n"
# define MULTI_SPAWN ": Redefine of spawn, please use only one !\n"
# define NO_SPAWN "Error\nNo spawn in map !\n"
# define COPY_ERROR "Error\nMap copy failed !\n"
# define INV_HDR "Error\nInvalid line in map header !\n"
# define ERROR_ASSETS "Error\nAssets init failed !\n"
# define ERROR_PLAYER "Error\nPlayer init failed !\n"
# define ERROR_MAP "Error\nMap init failed !\n"
# define ERROR_GAME "Error\nGame init failed !\n"
# define ERROR_MLX "Error\nMlx init failed !\n"

#endif
