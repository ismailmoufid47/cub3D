#include "../../include/cub3D_bonus.h"

void	draw_square(t_all_data	*all_data, int x, int y, uint32_t color)
{
	int			y2;
	int			x2;
	int			size;
	uint32_t	*pixels;


	if (WIDTH <= HEIGHT)
		size = WIDTH / MINIMAP_SIZE;
	else
		size = HEIGHT / MINIMAP_SIZE;
	pixels = all_data->window_pixels;
	y2 = 0;
	while (y2 < size)
	{
		x2 = 0;
		while (x2 < size)
		{
			pixels[(y + y2) * WIDTH + (x + x2)] = color;
			x2++;
		}
		y2++;
	}
}

void	init_indicator_data(int *start_x, int *start_y, int *indicator_size)
{
	if (WIDTH <= HEIGHT)
	{
		*start_y = (WIDTH / MINIMAP_SIZE * MINIMAP_RADIUS)
			+ (WIDTH / MINIMAP_SIZE * 0.5);
		*start_x = (WIDTH / MINIMAP_SIZE * MINIMAP_RADIUS)
			+ (WIDTH / MINIMAP_SIZE * 0.5);
		*indicator_size = WIDTH / MINIMAP_SIZE / 5;
	}
	else
	{
		*start_y = (HEIGHT / MINIMAP_SIZE * MINIMAP_RADIUS)
			+ (HEIGHT / MINIMAP_SIZE * 0.5);
		*start_x = (HEIGHT / MINIMAP_SIZE * MINIMAP_RADIUS)
			+ (HEIGHT / MINIMAP_SIZE * 0.5);
		*indicator_size = HEIGHT / MINIMAP_SIZE / 5;
	}
}

void	draw_player_indicator(t_all_data *all_data)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	indicator_size;

	init_indicator_data(&start_x, &start_y, &indicator_size);
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
	char	tile;

	if (map_y < 0 || map_x < 0)
		return (UINT32_C(0xFF000000));

	if (!all_data->map || !all_data->map[map_y])
		return (UINT32_C(0xFF000000));

	if ((size_t)map_x >= ft_strlen(all_data->map[map_y]))
		return (UINT32_C(0xFF000000));
	tile = all_data->map[map_y][map_x];
	if (tile == '1')
		return ((UINT32_MAX));
	else if (tile == 'D' || tile == 'C')
		return (UINT32_C(0xFF00FF00));
	else
		return (UINT32_C(0xFF000000));
}


void	draw_minimap(t_all_data *all_data)
{
	int	size;
	int	dy;
	int	dx;

	if (WIDTH <= HEIGHT)
		size = WIDTH / MINIMAP_SIZE;
	else
		size = HEIGHT / MINIMAP_SIZE;
	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		dx = -MINIMAP_RADIUS;
		while (dx <= MINIMAP_RADIUS)
		{
			draw_square(all_data, (dx + MINIMAP_RADIUS) * size,
				(dy + MINIMAP_RADIUS) * size,
				get_tile_color(all_data,
					(int)all_data->player->x + dx,
					(int)all_data->player->y + dy));
			dx++;
		}
		dy++;
	}
	draw_player_indicator(all_data);
}

