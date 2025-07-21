#include "../include/cub3D.h"

void	draw_ray(t_ray *rays, t_mlx_image *image)
{
	int x0, y0, x1, y1;
	int dx, dy;
	int sx, sy;
	int err, e2;
	x0 = rays->start_x * TILE;
	y0 = rays->start_y * TILE;
	x1 = rays->end_x * TILE;
	y1 = rays->end_y * TILE;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		mlx_put_pixel(image, x0, y0, 0xFF);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_map(char **map, t_mlx_image *image)
{
	int	y;
	int	x;
	int	y2;
	int	x2;

	y = 0;
	x = 0;
	y2 = 0;
	x2 = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				y2 = 0;
				while (y2 < TILE)
				{
					x2 = 0;
					while (x2 < TILE)
					{
						mlx_put_pixel(image, x * TILE + x2, y * TILE + y2,
							0xFFFFFF);
						x2++;
					}
					y2++;
				}
			}
			else
			{
				y2 = 0;
				while (y2 < TILE)
				{
					x2 = 0;
					while (x2 < TILE)
					{
						mlx_put_pixel(image, x * TILE + x2, y * TILE + y2, 0x0);
						x2++;
					}
					y2++;
				}
			}
			x++;
		}
		y++;
	}
}

void	init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->start_x = player->x;
	ray->start_y = player->y;
	ray->end_x = 0;
	ray->end_y = 0;
	ray->angle = angle;
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	if (ray->angle >= 2 * M_PI)
		ray->angle -= 2 * M_PI;
}

void	ray_casting(t_all_data *all_data, t_ray *ray, double angle)
{
	double	x_ray_direction;
	double	y_ray_direction;
	double	delta_x;
	double	delta_y;
	double	ray_distance_x;
	double	ray_distance_y;
	int		map_x;
	int		map_y;

	init_ray(ray, all_data->player, angle);
	x_ray_direction = cos(angle);
	y_ray_direction = sin(angle);
	ray_distance_x = 0;
	ray_distance_y = 0;
	map_x = (int)(all_data->player->x);
	map_y = (int)all_data->player->y;
	if (x_ray_direction == 0)
		delta_x = INFINITY;
	else
		delta_x = fabs(1 / x_ray_direction);
	if (y_ray_direction == 0)
		delta_y = INFINITY;
	else
		delta_y = fabs(1 / y_ray_direction);
	if (x_ray_direction > 0)
		ray_distance_x = delta_x * ((map_x + 1) - all_data->player->x);
	else if (x_ray_direction < 0)
		ray_distance_x = delta_x * (all_data->player->x - map_x);
	else
		ray_distance_x = INFINITY;
	if (y_ray_direction > 0)
		ray_distance_y = delta_y * ((map_y + 1) - all_data->player->y);
	else if (y_ray_direction < 0)
		ray_distance_y = delta_y * (all_data->player->y - map_y);
	else
		ray_distance_y = INFINITY;
	double distance_to_wall = 0;
	while (all_data->map[map_y][map_x] != '1')
	{
		distance_to_wall = ray_distance_x;
		if (ray_distance_x < ray_distance_y)
		{
			if (all_data->map[map_y][map_x] != '1')
			{
				if (x_ray_direction > 0)
					map_x += 1;
				else
					map_x -= 1;
				ray_distance_x += delta_x;
				ray->hit_type = VERTICAL;
			}
		}
		else
		{
			distance_to_wall = ray_distance_y;
			if (all_data->map[map_y][map_x] != '1')
			{
				if (y_ray_direction > 0)
					map_y += 1;
				else
					map_y -= 1;
				ray_distance_y += delta_y;
				ray->hit_type = HORIZONTAL;
			}
		}
	}
	ray->end_y = all_data->player->y + distance_to_wall * y_ray_direction;
	ray->end_x = all_data->player->x + distance_to_wall * x_ray_direction;
	return ;
}

void	cast_rays(t_all_data *all_data)
{
	double	angle;
	int		i;

	angle = all_data->player->direction - ((FOV * M_PI / 180) / 2);
	i = 0;
	while (i < WIDTH)
	{
		angle += ((FOV * M_PI / 180) / WIDTH);
		ray_casting(all_data, &all_data->rays[i], angle);
		i++;
	}
	i = 0;
	while (i < WIDTH)
		i++;
}
