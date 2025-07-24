#include "../../include/cub3D.h"

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

double	calculate_hit_offset(t_ray *ray, int wall_type)
{
	double	hit_offset;

	if (wall_type == EAST || wall_type == WEST)
	{
		hit_offset = ray->end_y - (int)ray->end_y;
		if (wall_type == WEST)
			hit_offset = 1.0f - hit_offset;
	}
	else
	{
		hit_offset = ray->end_x - (int)ray->end_x;
		if (wall_type == SOUTH)
			hit_offset = 1.0f - hit_offset;
	}
	if (hit_offset < 0)
		hit_offset += 1.0f;
	if (hit_offset >= 1.0f)
		hit_offset -= 1.0f;
	return (hit_offset);
}

void	calculate_wall_bounds(double distance, int *start_y, int *end_y)
{
	int	wall_screen_height;

	wall_screen_height = (int)(HEIGHT / distance);
	*start_y = HEIGHT / 2 - wall_screen_height / 2;
	*end_y = HEIGHT / 2 + wall_screen_height / 2;
	if (*start_y < 0)
		*start_y = 0;
	if (*end_y >= HEIGHT)
		*end_y = HEIGHT - 1;
}

int	get_texture_x(double hit_offset, t_mlx_texture *texture)
{
	int	tex_x;

	if (!texture)
		return (0);
	if (texture->width <= 0)
		return (0);
	if (hit_offset < 0)
		hit_offset += 1.0f;
	if (hit_offset >= 1.0f)
		hit_offset -= 1.0f;
	tex_x = (int)(hit_offset * texture->width);
	return (tex_x);
}
