/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   rendering_bonus.c                                                        */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:35:48 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:35:48 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	draw_background(t_all_data *all_data)
{
	uint32_t	*screen_pixels;
	int			half_pixels;
	int			i;

	screen_pixels = all_data->window_pixels;
	half_pixels = (WIDTH * HEIGHT) / 2;
	i = 0;
	while (i < half_pixels)
	{
		screen_pixels[i] = all_data->ceiling_color;
		i++;
	}
	while (i < WIDTH * HEIGHT)
	{
		screen_pixels[i] = all_data->floor_color;
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
