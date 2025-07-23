#include "../include/cub3D.h"

void	init_input_state(t_all_data *all_data)
{
	all_data->input_state = malloc(sizeof(t_input_state));
	if (!all_data->input_state)
		return ;
	all_data->input_state->w_pressed = 0;
	all_data->input_state->s_pressed = 0;
	all_data->input_state->a_pressed = 0;
	all_data->input_state->d_pressed = 0;
	all_data->input_state->left_pressed = 0;
	all_data->input_state->right_pressed = 0;
}

static void	handle_key_press(t_all_data *all_data, t_mlx_key_data keydata)
{
	if (keydata.key == MLX_KEY_W)
		all_data->input_state->w_pressed = true;
	else if (keydata.key == MLX_KEY_S)
		all_data->input_state->s_pressed = true;
	else if (keydata.key == MLX_KEY_A)
		all_data->input_state->a_pressed = true;
	else if (keydata.key == MLX_KEY_D)
		all_data->input_state->d_pressed = true;
	else if (keydata.key == MLX_KEY_LEFT)
		all_data->input_state->left_pressed = true;
	else if (keydata.key == MLX_KEY_RIGHT)
		all_data->input_state->right_pressed = true;
	else if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(all_data->mlx);
}

static void	handle_key_release(t_all_data *all_data, t_mlx_key_data keydata)
{
	if (keydata.key == MLX_KEY_W)
		all_data->input_state->w_pressed = false;
	else if (keydata.key == MLX_KEY_S)
		all_data->input_state->s_pressed = false;
	else if (keydata.key == MLX_KEY_A)
		all_data->input_state->a_pressed = false;
	else if (keydata.key == MLX_KEY_D)
		all_data->input_state->d_pressed = false;
	else if (keydata.key == MLX_KEY_LEFT)
		all_data->input_state->left_pressed = false;
	else if (keydata.key == MLX_KEY_RIGHT)
		all_data->input_state->right_pressed = false;
}

void	key_press_hook(t_mlx_key_data keydata, void *all_dat)
{
	t_all_data	*all_data;

	all_data = (t_all_data *)all_dat;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		handle_key_press(all_data, keydata);
	else if (keydata.action == MLX_RELEASE)
		handle_key_release(all_data, keydata);
}
