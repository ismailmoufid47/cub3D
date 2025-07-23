#include "../include/cub3D.h"

// void	draw_ray(t_ray *rays, t_mlx_image *image)
// {
// 	int x0, y0, x1, y1;
// 	int dx, dy;
// 	int sx, sy;
// 	int err, e2;
// 	x0 = rays->start_x * TILE;
// 	y0 = rays->start_y * TILE;
// 	x1 = rays->end_x * TILE;
// 	y1 = rays->end_y * TILE;
// 	dx = abs(x1 - x0);
// 	dy = abs(y1 - y0);
// 	sx = (x0 < x1) ? 1 : -1;
// 	sy = (y0 < y1) ? 1 : -1;
// 	err = dx - dy;
// 	while (1)
// 	{
// 		mlx_put_pixel(image, x0, y0, 0xFF);
// 		if (x0 == x1 && y0 == y1)
// 			break ;
// 		e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// void	draw_map(char **map, t_mlx_image *image)
// {
// 	int	y;
// 	int	x;
// 	int	y2;
// 	int	x2;

// 	y = 0;
// 	x = 0;
// 	y2 = 0;
// 	x2 = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == '1')
// 			{
// 				y2 = 0;
// 				while (y2 < TILE)
// 				{
// 					x2 = 0;
// 					while (x2 < TILE)
// 					{
// 						mlx_put_pixel(image, x * TILE + x2, y * TILE + y2,
// 							0xFFFFFF);
// 						x2++;
// 					}
// 					y2++;
// 				}
// 			}
// 			else
// 			{
// 				y2 = 0;
// 				while (y2 < TILE)
// 				{
// 					x2 = 0;
// 					while (x2 < TILE)
// 					{
// 						mlx_put_pixel(image, x * TILE + x2, y * TILE + y2, 0x0);
// 						x2++;
// 					}
// 					y2++;
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	calculate_initial_distances(t_ray_cast_data *data,
		t_all_data *all_data)
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

void	step_horizontal(t_ray_cast_data *data, t_all_data *all_data,
		t_ray *ray)
{
	data->distance_to_wall = data->ray_distance_y;
	if (all_data->map[data->map_y][data->map_x] != '1')
	{
		if (data->y_ray_direction > 0)
			data->map_y += 1;
		else
			data->map_y -= 1;
		data->ray_distance_y += data->delta_y;
		ray->hit_type = HORIZONTAL;
	}
}

void	step_vertical(t_ray_cast_data *data, t_all_data *all_data,
		t_ray *ray)
{
	data->distance_to_wall = data->ray_distance_x;
	if (all_data->map[data->map_y][data->map_x] != '1')
	{
		if (data->x_ray_direction > 0)
			data->map_x += 1;
		else
			data->map_x -= 1;
		data->ray_distance_x += data->delta_x;
		ray->hit_type = VERTICAL;
	}
}

void	perform_dda(t_ray_cast_data *data, t_all_data *all_data,
		t_ray *ray)
{
	while (all_data->map[data->map_y][data->map_x] != '1')
	{
		if (data->ray_distance_x < data->ray_distance_y)
			step_vertical(data, all_data, ray);
		else
			step_horizontal(data, all_data, ray);
	}
	ray->end_x = all_data->player->x + data->distance_to_wall
		* data->x_ray_direction;
	ray->end_y = all_data->player->y + data->distance_to_wall
		* data->y_ray_direction;
}

void	cast_rays(t_all_data *all)
{
	t_ray_cast_data	data;
	double			ray_angle;
	int				screen_x_offset_from_center;
	int				screen_x;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		screen_x_offset_from_center = screen_x - (WIDTH / 2);
		ray_angle = all->player->direction
			+ atan2(screen_x_offset_from_center, (WIDTH / 2));
		init_ray(&all->rays[screen_x], all->player, ray_angle);
		init_ray_cast_data(&data, all, ray_angle);
		calculate_deltas(&data);
		calculate_initial_distances(&data, all);
		perform_dda(&data, all, &all->rays[screen_x]);
		screen_x++;
	}
}
