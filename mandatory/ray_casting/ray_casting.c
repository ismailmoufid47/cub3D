#include "../../include/cub3D.h"

void	ray_casting(t_all_data *all_data,float angle)
{
	float x_ray_direction = cos(angle);
	float y_ray_direction = sin(angle);
	float delta_x;
	float delta_y;

	if (x_ray_direction == 0)
		delta_x = FLT_MAX;
	else
		delta_x = fabs(1 / x_ray_direction);
	if (y_ray_direction == 0)
		delta_y = FLT_MAX;
	else
		delta_y = fabs(1 / y_ray_direction);
	float ray_x_col = 0;
	float ray_y_col = 0;
	int map_x_pos = player.x;
	int map_y_pos = player.y;
	if (x_ray_direction > 0)
		ray_x_col = delta_x * (1.0 - (player.x - (int)player.x));
	else if (x_ray_direction < 0)
		ray_x_col = delta_x * (player.x - (int)player.x);
	if (y_ray_direction > 0)
		ray_y_col = delta_y * (1.0 - (player.y - (int)player.y));
	else if (y_ray_direction < 0)
		ray_y_col = delta_y * (player.y - (int)player.y);
	while(map[map_y_pos][map_x_pos] != 1)
	{
		if(ray_x_col < ray_y_col)
		{
			if (dx > 0)
				map_x_pos += 1;
			else
				map_x_pos -= 1;
			ray_x_col += delta_x;

		}
		else
		{
			if (dx < 0)
				map_y_pos += 1;
			else
				map_y_pos -= 1;
			map_y_pos += 1;
			ray_y_col += delta_y;
		}
	}
	return ;
}