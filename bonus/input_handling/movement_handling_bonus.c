#include "../include/cub3D_bonus.h"

static int	is_valid_position(t_all_data *all_data, double x, double y)
{
	double	buffer;

	buffer = 0.1;
	if (all_data->map[(int)(y - buffer)][(int)(x - buffer)] == '1' ||
		all_data->map[(int)(y - buffer)][(int)(x + buffer)] == '1' ||
		all_data->map[(int)(y + buffer)][(int)(x - buffer)] == '1' ||
		all_data->map[(int)(y + buffer)][(int)(x + buffer)] == '1')
		return (0);
	return (1);
}

static void	handle_movement(t_all_data *all_data, double move_direction)
{
	double	new_x;
	double	new_y;
	double	x;
	double	y;

	x = all_data->player->x;
	y = all_data->player->y;
	new_x = x + cos(move_direction) * MOVEMENT_SPEED;
	new_y = y + sin(move_direction) * MOVEMENT_SPEED;
	if (is_valid_position(all_data, new_x, new_y))
	{
		all_data->player->x = new_x;
		all_data->player->y = new_y;
	}
	else
	{
		if (is_valid_position(all_data, new_x, y))
			all_data->player->x = new_x;
		else if (is_valid_position(all_data, x, new_y))
			all_data->player->y = new_y;
	}
}

static void	handle_rotation(t_all_data *all_data, int *rotation_occurred)
{
	if (all_data->input_state->left_pressed)
	{
		all_data->player->direction -= KEY_ROTATION_SPEED;
		*rotation_occurred = 1;
	}
	if (all_data->input_state->right_pressed)
	{
		all_data->player->direction += KEY_ROTATION_SPEED;
		*rotation_occurred = 1;
	}
	if (all_data->input_state->mouse_moved_left
		|| all_data->input_state->mouse_moved_right)
	{
		if (all_data->input_state->mouse_moved_right)
			all_data->player->direction += MOUSE_ROTATION_SPEED;
		else
			all_data->player->direction -= MOUSE_ROTATION_SPEED;
		*rotation_occurred = 1;
		all_data->input_state->mouse_moved_right = false;
		all_data->input_state->mouse_moved_left = false;
	}
	if (all_data->player->direction < 0)
		all_data->player->direction += 2 * M_PI;
	if (all_data->player->direction >= 2 * M_PI)
		all_data->player->direction -= 2 * M_PI;
}

static void	handle_player_movement(t_all_data *all_data, int *movement_occurred)
{
	if (all_data->input_state->w_pressed)
	{
		handle_movement(all_data, all_data->player->direction);
		*movement_occurred = 1;
	}
	if (all_data->input_state->s_pressed)
	{
		handle_movement(all_data, all_data->player->direction + M_PI);
		*movement_occurred = 1;
	}
	if (all_data->input_state->a_pressed)
	{
		handle_movement(all_data, all_data->player->direction - M_PI / 2);
		*movement_occurred = 1;
	}
	if (all_data->input_state->d_pressed)
	{
		handle_movement(all_data, all_data->player->direction + M_PI / 2);
		*movement_occurred = 1;
	}
}

void	game_loop(void *all_dat)
{
	t_all_data	*all_data;
	int			movement_occurred;
	int			rotation_occurred;

	all_data = (t_all_data *)all_dat;
	movement_occurred = 0;
	rotation_occurred = 0;
	handle_rotation(all_data, &rotation_occurred);
	handle_player_movement(all_data, &movement_occurred);
	if (movement_occurred || rotation_occurred)
	{
		toggle_doors_in_proximity(all_data);
		cast_rays(all_data);
		render(all_data);
	}
}
