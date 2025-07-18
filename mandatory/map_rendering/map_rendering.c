
#include "../include/cub3D.h"

void	draw_background(t_all_data *all_data)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(all_data->image, x, y, all_data->C_color);
			else
				mlx_put_pixel(all_data->image, x, y, all_data->F_color);
			x++;
		}
		y++;
	}
}

void	draw_one_wall(t_all_data *all_data, float distance, int ray_index)
{
	int	wall_height;
	int	wall_width;
	int	y;
	int	x;

	wall_height = (int)(WALL_HEIGHT / distance);
	wall_width = (int)(WIDTH / N_RAYS);
	y = HEIGHT / 2 - wall_height / 2;
	while (y < (HEIGHT / 2 + wall_height / 2))
	{
		x = ray_index * wall_width;
		while (x < ((ray_index + 1) * wall_width))
		{
			if (!(y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH))
				mlx_put_pixel(all_data->image, x, y, UINT32_MAX);
			x++;
		}
		y++;
	}
}

void	draw_walls(t_all_data *all_data)
{
	int		i;
	float	distance;

	i = 0;
	while (i < N_RAYS)
	{
		distance = sqrt(pow(all_data->rays[i].end_x - all_data->player->x, 2)
				+ pow(all_data->rays[i].end_y - all_data->player->y, 2));
		distance = distance * cos(all_data->rays[i].angle
				- all_data->player->direction);
		draw_one_wall(all_data, distance, i);
		i++;
	}
}

void	ft_cub3D(t_all_data *all_data)
{
	cast_rays(all_data);
	draw_background(all_data);
	draw_walls(all_data);
}
