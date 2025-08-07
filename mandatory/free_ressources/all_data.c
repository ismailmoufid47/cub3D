/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-amr <moel-amr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:33:37 by moel-amr          #+#    #+#             */
/*   Updated: 2025/08/07 12:33:37 by moel-amr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_all_data(t_all_data *all_data)
{
	ft_free_split(all_data->map);
	ft_free_split(all_data->textures_and_colors);
	free(all_data->player);
	free(all_data->input_state);
	free(all_data->rays);
	mlx_delete_texture(all_data->textures[NORTH]);
	mlx_delete_texture(all_data->textures[SOUTH]);
	mlx_delete_texture(all_data->textures[WEST]);
	mlx_delete_texture(all_data->textures[EAST]);
	free(all_data);
}
