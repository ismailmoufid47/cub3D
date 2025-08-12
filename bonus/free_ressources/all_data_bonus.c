/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   all_data_bonus.c                                                         */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:35:15 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:35:16 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	free_all_data(t_all_data *all_data)
{
	int	i;

	ft_free_split(all_data->map);
	ft_free_split(all_data->textures_and_colors);
	free(all_data->player);
	free(all_data->input_state);
	free(all_data->rays);
	i = -1;
	while (++i < 21)
		mlx_delete_texture(all_data->textures[i]);
	mlx_delete_image(all_data->mlx, all_data->window_image);
	mlx_terminate(all_data->mlx);
	free(all_data);
}
