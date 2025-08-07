/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-amr <moel-amr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:34:18 by moel-amr          #+#    #+#             */
/*   Updated: 2025/08/07 12:34:18 by moel-amr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	mlx_init_error(t_all_data *all_data)
{
	free(all_data);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

void	post_textures_and_colors_error(char **textures_and_colors, int fd)
{
	close(fd);
	ft_free_split(textures_and_colors);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}
