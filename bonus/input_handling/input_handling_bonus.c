/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   input_handling_bonus.c                                                   */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:35:31 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:35:31 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	init_input_state(t_all_data *all_data)
{
	all_data->input_state = malloc(sizeof(t_input_state));
	if (!all_data->input_state)
		return ;
	all_data->input_state->w_pressed = false;
	all_data->input_state->s_pressed = false;
	all_data->input_state->a_pressed = false;
	all_data->input_state->d_pressed = false;
	all_data->input_state->left_pressed = false;
	all_data->input_state->right_pressed = false;
	all_data->input_state->mouse_moved_left = false;
	all_data->input_state->mouse_moved_right = false;
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
	if (keydata.action == MLX_PRESS)
		handle_key_press(all_data, keydata);
	else if (keydata.action == MLX_RELEASE)
		handle_key_release(all_data, keydata);
}

void	mouse_move_hook(double xpos, double ypos, void *all_dat)
{
	t_all_data	*all_data;
	double		mouse_delta;

	(void)ypos;
	all_data = (t_all_data *)all_dat;
	mouse_delta = xpos - (WIDTH / 2.0);
	all_data->input_state->mouse_moved_left = false;
	all_data->input_state->mouse_moved_right = false;
	if (fabs(mouse_delta) > 1.0)
	{
		if (mouse_delta > 0)
			all_data->input_state->mouse_moved_right = true;
		else
			all_data->input_state->mouse_moved_left = true;
		mlx_set_mouse_pos(all_data->mlx, WIDTH / 2, HEIGHT / 2);
	}
}
