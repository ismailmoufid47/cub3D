#include "../include/cub3D_bonus.h"

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
	mlx_delete_texture(all_data->textures[DOOR]);
	free(all_data);
}

