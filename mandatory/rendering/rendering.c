/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   rendering.c                                                              */
/*                                                                            */
/*   By: moel-amr & isel-mou                                                  */
/*                                                                            */
/*   Created: 2025/08/07 12:34:51 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:35:05 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_background(t_all_data *all_data)
{
	uint32_t	*screen_pixels;
	int			half_pixels;
	int			i;

	screen_pixels = (uint32_t *)all_data->window_pixels;
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

void	render_wall_column(uint32_t *screen_pixels, uint32_t *tex_pixels, int x,
		t_wall_render_params params)
{
	int		y;
	int		wall_screen_height;
	int		original_start_y;
	double	tex_y_ratio;
	int		tex_y;

	y = params.start_y;
	wall_screen_height = (int)(HEIGHT / params.distance);
	original_start_y = HEIGHT / 2 - wall_screen_height / 2;
	while (y <= params.end_y)
	{
		tex_y_ratio = (double)(y - original_start_y) / wall_screen_height;
		tex_y = (int)(tex_y_ratio * params.texture_height);
		if (tex_y >= params.texture_height)
			tex_y = params.texture_height - 1;
		if (tex_y < 0)
			tex_y = 0;
		screen_pixels[y * WIDTH + x] = tex_pixels[tex_y * params.texture_width
			+ params.tex_x];
		y++;
	}
}

void	show_ray_on_screen(t_all_data *all_data, double distance, int screen_x)
{
	int						wall_type;
	double					hit_offset;
	t_wall_render_params	params;

	if (screen_x < 0 || screen_x >= WIDTH)
		return ;
	wall_type = get_wall_type(&all_data->rays[screen_x]);
	hit_offset = calculate_hit_offset(&all_data->rays[screen_x], wall_type);
	calculate_wall_bounds(distance, &params.start_y, &params.end_y);
	if (params.end_y - params.start_y <= 0)
		return ;
	params.distance = distance;
	params.tex_x = get_texture_x(hit_offset, all_data->textures[wall_type]);
	params.texture_width = all_data->textures[wall_type]->width;
	params.texture_height = all_data->textures[wall_type]->height;
	render_wall_column((uint32_t *)all_data->window_pixels,
		(uint32_t *)all_data->textures[wall_type]->pixels, screen_x, params);
}

void	draw_walls(t_all_data *all_data)
{
	int		i;
	double	distance;

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

void	render(t_all_data *all_data)
{
	draw_background(all_data);
	draw_walls(all_data);
}
