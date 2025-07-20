
#include "../include/cub3D.h"

void	draw_background(t_all_data *all_data)
{
	uint32_t	*pixels;
	int			half_pixels;
	int			i;

	pixels = (uint32_t *)all_data->image->pixels;
	half_pixels = (WIDTH * HEIGHT) / 2;
	i = 0;
	while (i < half_pixels)
	{
		pixels[i] = all_data->ceiling_color;
		i++;
	}
	while (i < WIDTH * HEIGHT)
	{
		pixels[i] = all_data->floor_color;
		i++;
	}
}

int	get_wall_type(t_ray *ray)
{
	if (ray->hit_type == VERTICAL)
	{
		if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->angle > 0 && ray->angle < M_PI)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	show_ray_on_screen(t_all_data *all_data, float distance, int x)
{
	int         start_y;
	int         end_y_screen;
	int         y;
	uint32_t    *pixels;
	uint32_t    *tex_pixels;
	int         tex_y;
	int         tex_x;
	float       tex_y_ratio;
	int         wall_direction;
	float       hit_offset;

	wall_direction = get_wall_type(&all_data->rays[x]);
	if (wall_direction == EAST || wall_direction == WEST)
	{
		hit_offset = all_data->rays[x].end_y - (int)all_data->rays[x].end_y;
		if (wall_direction == WEST)
			hit_offset = 1.0f - hit_offset;
	}
	else
	{
		hit_offset = all_data->rays[x].end_x - (int)all_data->rays[x].end_x;
		if (wall_direction == SOUTH)
			hit_offset = 1.0f - hit_offset;
	}

	if (hit_offset < 0)
		hit_offset += 1.0f;
	if (hit_offset >= 1.0f)
		hit_offset -= 1.0f;

		end_y_screen = HEIGHT / 2 + (int)(HEIGHT * WALL_HEIGHT / distance) / 2;
		pixels = (uint32_t *)all_data->image->pixels;
		tex_pixels = (uint32_t *)all_data->textures[wall_direction]->pixels;
		tex_x = (int)(hit_offset * all_data->textures[wall_direction]->width);
		
	if (tex_x >= (int)all_data->textures[wall_direction]->width)
		tex_x = all_data->textures[wall_direction]->width - 1;
	if (tex_x < 0)
		tex_x = 0;

	start_y = HEIGHT / 2 - (int)(HEIGHT * WALL_HEIGHT / distance) / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y_screen >= HEIGHT)
		end_y_screen = HEIGHT - 1;
	if (x < 0 || x >= WIDTH)
		return ;
	if (end_y_screen - start_y <= 0)
		return ;
	y = start_y;
	while (y <= end_y_screen)
	{
		tex_y_ratio = (float)(y - (HEIGHT / 2 - (int)(HEIGHT * WALL_HEIGHT / distance) / 2)) / (int)(HEIGHT * WALL_HEIGHT / distance);
		tex_y = (int)(tex_y_ratio * all_data->textures[wall_direction]->height);
		if (tex_y >= (int)all_data->textures[wall_direction]->height)
			tex_y = all_data->textures[wall_direction]->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		pixels[y * WIDTH + x] = tex_pixels[tex_y * all_data->textures[wall_direction]->width + tex_x];
		y++;
	}
}

void	draw_walls(t_all_data *all_data)
{
	int		i;
	float	distance;

	i = 0;
	while (i < WIDTH)
	{
		distance = sqrt(pow(all_data->rays[i].end_x - all_data->player->x, 2)
				+ pow(all_data->rays[i].end_y - all_data->player->y, 2));
		distance = distance * cos(all_data->rays[i].angle
				- all_data->player->direction);
		show_ray_on_screen(all_data, distance, i);
		i++;
	}
}

void	ft_cub3d(t_all_data *all_data)
{
	draw_background(all_data);
	draw_walls(all_data);
}
