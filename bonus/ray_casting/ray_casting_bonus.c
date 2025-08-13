/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ray_casting_bonus.c                                                      */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:36:59 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:36:59 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	calculate_initial_distances(t_ray_cast_data *data, t_all_data *all_data)
{
	if (data->x_ray_direction > 0)
		data->ray_distance_x = data->delta_x * ((data->map_x + 1)
				- all_data->player->x);
	else if (data->x_ray_direction < 0)
		data->ray_distance_x = data->delta_x * (all_data->player->x
				- data->map_x);
	else
		data->ray_distance_x = INFINITY;
	if (data->y_ray_direction > 0)
		data->ray_distance_y = data->delta_y * ((data->map_y + 1)
				- all_data->player->y);
	else if (data->y_ray_direction < 0)
		data->ray_distance_y = data->delta_y * (all_data->player->y
				- data->map_y);
	else
		data->ray_distance_y = INFINITY;
}

void	step_in_y(t_ray_cast_data *data, t_all_data *all_data, t_ray *ray)
{
	data->distance_to_wall = data->ray_distance_y;
	if (all_data->map[data->map_y][data->map_x] != '1'
		&& all_data->map[data->map_y][data->map_x] != 'D')
	{
		if (data->y_ray_direction > 0)
			data->map_y += 1;
		else
			data->map_y -= 1;
		data->ray_distance_y += data->delta_y;
		ray->hit_type = HORIZONTAL;
	}
}

void	step_in_x(t_ray_cast_data *data, t_all_data *all_data, t_ray *ray)
{
	data->distance_to_wall = data->ray_distance_x;
	if (all_data->map[data->map_y][data->map_x] != '1'
		&& all_data->map[data->map_y][data->map_x] != 'D')
	{
		if (data->x_ray_direction > 0)
			data->map_x += 1;
		else
			data->map_x -= 1;
		data->ray_distance_x += data->delta_x;
		ray->hit_type = VERTICAL;
	}
}

void	perform_dda(t_ray_cast_data *data, t_all_data *all_data, t_ray *ray)
{
	while (all_data->map[data->map_y][data->map_x] != '1'
		&& all_data->map[data->map_y][data->map_x] != 'D')
	{
		if (data->ray_distance_x < data->ray_distance_y)
			step_in_x(data, all_data, ray);
		else
			step_in_y(data, all_data, ray);
	}
	if (all_data->map[data->map_y][data->map_x] == '1')
		ray->whats_hit = WALL_HIT;
	else
		ray->whats_hit = DOOR_HIT;
	ray->end_x = all_data->player->x + data->distance_to_wall
		* data->x_ray_direction;
	ray->end_y = all_data->player->y + data->distance_to_wall
		* data->y_ray_direction;
}

void	cast_rays(t_all_data *all)
{
	t_ray_cast_data	data;
	int				screen_x;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		init_ray_cast_data(all, &data, &all->rays[screen_x], screen_x);
		calculate_initial_distances(&data, all);
		perform_dda(&data, all, &all->rays[screen_x]);
		screen_x++;
	}
}
