/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   render_minimap_bonus.c                                                   */
/*                                                 isel-mou@student.1337.ma   */
/*   By: moel-amr & isel-mou                       moel-amr@student.1337.ma   */
/*                                                                            */
/*   Created: 2025/08/07 12:37:09 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:37:09 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	init_indicator_data(t_all_data *all_data, int *start_x,
		int *start_y, int *indicator_size)
{
	int		scale;
	int		center;
	double	frac_x;
	double	frac_y;

	scale = HEIGHT / MINIMAP_SIZE;
	if (WIDTH <= HEIGHT)
		scale = WIDTH / MINIMAP_SIZE;
	center = (scale * MINIMAP_RADIUS);
	frac_x = all_data->player->x - (int)all_data->player->x;
	frac_y = all_data->player->y - (int)all_data->player->y;
	*start_x = center + (int)(frac_x * scale);
	*start_y = center + (int)(frac_y * scale);
	*indicator_size = scale / 4;
}

void	draw_player_indicator(t_all_data *all_data)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	indicator_size;

	init_indicator_data(all_data, &start_x, &start_y, &indicator_size);
	y = start_y;
	while (y < start_y + indicator_size && y < HEIGHT)
	{
		x = start_x;
		while (x < start_x + indicator_size && x < WIDTH)
		{
			all_data->window_pixels[y * WIDTH + x] = UINT32_C(0xFFFF0000);
			x++;
		}
		y++;
	}
}

uint32_t	get_tile_color(t_all_data *all_data, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= get_map_height(all_data->map))
		return (0);
	if (map_x < 0 || map_x >= get_map_width(all_data->map[map_y]))
		return (0);
	if (all_data->map[map_y][map_x] == '1')
		return (UINT32_MAX);
	else if (all_data->map[map_y][map_x] == 'D')
		return (UINT32_C(0xFF00FF00));
	else if (all_data->map[map_y][map_x] == 'C')
		return (UINT32_C(0xFFFF0000));
	return (UINT32_C(0xFF000000));
}

void	draw_tile_block(t_all_data *all_data,
	int pixel_x, int pixel_y, uint32_t color)
{
	int	scale;
	int	end_x;
	int	end_y;
	int	y;
	int	x;

	scale = HEIGHT / MINIMAP_SIZE;
	if (WIDTH <= HEIGHT)
		scale = WIDTH / MINIMAP_SIZE;
	end_x = pixel_x + scale;
	if (end_x > WIDTH)
		end_x = WIDTH;
	end_y = pixel_y + scale;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	y = -1;
	while (++y < end_y - pixel_y)
	{
		x = -1;
		while (++x < end_x - pixel_x)
			all_data->window_pixels
			[(pixel_y + y) * WIDTH + pixel_x + x] = color;
	}
}

void	draw_minimap(t_all_data *all_data)
{
	uint32_t	color;
	int			scale;
	int			dy;
	int			dx;

	scale = HEIGHT / MINIMAP_SIZE;
	if (WIDTH <= HEIGHT)
		scale = WIDTH / MINIMAP_SIZE;
	dy = -MINIMAP_RADIUS - 1;
	while (++dy <= MINIMAP_RADIUS)
	{
		dx = -MINIMAP_RADIUS - 1;
		while (++dx <= MINIMAP_RADIUS)
		{
			color = get_tile_color(all_data,
					(int)all_data->player->x + dx,
					(int)all_data->player->y + dy);
			if (color != 0)
				draw_tile_block(all_data,
					(MINIMAP_RADIUS + dx) * scale,
					(MINIMAP_RADIUS + dy) * scale,
					color);
		}
	}
	draw_player_indicator(all_data);
}
