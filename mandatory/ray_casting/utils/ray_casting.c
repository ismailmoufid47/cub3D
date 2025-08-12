/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ray_casting.c                                                            */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:33:45 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:33:50 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_ray_cast_data(t_all_data *all_data,
	t_ray_cast_data *casting_data, t_ray *ray, int screen_x)
{
	int		screen_x_offset_from_center;
	double	ray_angle;

	screen_x_offset_from_center = screen_x - (WIDTH / 2);
	ray_angle = all_data->player->direction + atan2(screen_x_offset_from_center,
			(WIDTH / 2));
	ray->start_x = all_data->player->x;
	ray->start_y = all_data->player->y;
	ray->end_x = 0;
	ray->end_y = 0;
	ray->angle = ray_angle;
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	if (ray->angle >= 2 * M_PI)
		ray->angle -= 2 * M_PI;
	casting_data->x_ray_direction = cos(ray_angle);
	casting_data->y_ray_direction = sin(ray_angle);
	casting_data->ray_distance_x = 0;
	casting_data->ray_distance_y = 0;
	casting_data->map_x = (int)(all_data->player->x);
	casting_data->map_y = (int)(all_data->player->y);
	casting_data->distance_to_wall = 0;
	casting_data->delta_x = fabs(1 / casting_data->x_ray_direction);
	casting_data->delta_y = fabs(1 / casting_data->y_ray_direction);
}
