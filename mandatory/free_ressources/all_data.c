/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   all_data.c                                                               */
/*                                                 isel-mou@student.1337.ma   */
/*   By: moel-amr & isel-mou                       moel-amr@student.1337.ma   */
/*                                                                            */
/*   Created: 2025/08/07 12:33:37 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:33:37 by moel-amr & isel-mou                      */
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
	mlx_delete_image(all_data->mlx, all_data->window_image);
	mlx_terminate(all_data->mlx);
	free(all_data);
}
