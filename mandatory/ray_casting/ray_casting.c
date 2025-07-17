#include "../../include/cub3D.h"

draw_map(char **map)
{
	int y = 0;
	int x = 0;
	int i = 0;
	int j = 0;

	while(map[y] != NULL)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				while (i < 10)
				{
					while (j < 10)
					{
						ft_put_pixel()
						j++;
					}
					i++;
				}
			}
			y++;
		}
		x++;
	}
}

void	ray_casting(t_all_data *all_data, float angle)
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
	int map_x_pos = (int)player.x;
	int map_y_pos = (int)player.y;
	if (x_ray_direction > 0)
		ray_x_col = delta_x * 1.0 - (player.x - (map_x));
	else if (x_ray_direction < 0)
		ray_x_col = delta_x * (player.x - map_x);
	if (y_ray_direction > 0)
		ray_y_col = delta_y * (1.0 - (player.y - map_y));
	else if (y_ray_direction < 0)
		ray_y_col = delta_y * (player.y - map_y);
	float x_hit;
	float y_hit;
	while (1337)
	{
		if (ray_x_col < ray_y_col)
		{
			if (dx > 0)
				map_x_pos += 1;
			else
				map_x_pos -= 1;

			ray_x_col += delta_x;
			if (map[map_y][map_x] == '1')
			{
				if (dx > 0)
					hit_x = map_x;
				else
					hit_x = map_x + 1;
				hit_y = player.y + ((hit_x - player_x) / x_ray_direction) * y_ray_direction;
				break;
			}
		}
		else
		{
			if (dx < 0)
				map_y_pos += 1;
			else
				map_y_pos -= 1;
			ray_y_col += delta_y;
			if (map[map_y][map_x] == '1')
			{
				if (dx > 0)
					hit_y = map_y;
				else
					hit_y = map_y + 1;
				hit_x = player.x + ((hit_y - player_y) / y_ray_direction) * x_ray_direction;
				break;
			}
		}
	}
	draw_map(map);
	return ;
}