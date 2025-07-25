#include "../include/cub3D_bonus.h"

void	render_wall_column(uint32_t *screen_pixels,
		uint32_t *tex_pixels, int x, t_wall_render_params params)
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
		screen_pixels[y * WIDTH + x]
			= tex_pixels[tex_y * params.texture_width + params.tex_x];
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
	if (all_data->rays[screen_x].whats_hit == DOOR_HIT)
		wall_type = DOOR;
	else
		wall_type = get_wall_type(&all_data->rays[screen_x]);
	hit_offset = calculate_hit_offset(&all_data->rays[screen_x],
			get_wall_type(&all_data->rays[screen_x]));
	calculate_wall_bounds(distance, &params.start_y, &params.end_y);
	if (params.end_y - params.start_y <= 0)
		return ;
	params.distance = distance;
	params.tex_x = get_texture_x(hit_offset, all_data->textures[wall_type]);
	params.texture_width = all_data->textures[wall_type]->width;
	params.texture_height = all_data->textures[wall_type]->height;
	render_wall_column(all_data->window_pixels,
		(uint32_t *)all_data->textures[wall_type]->pixels, screen_x, params);
}

void	draw_walls(t_all_data *all_data)
{
	int			i;
	double		distance;

	i = 0;
	while (i < WIDTH)
	{
		distance = sqrt(pow(all_data->rays[i].end_x - all_data->player->x, 2)
				+ pow(all_data->rays[i].end_y - all_data->player->y, 2));
		distance = distance
			* cos(all_data->rays[i].angle - all_data->player->direction);
		show_ray_on_screen(all_data, distance, i);
		i++;
	}
}

void	draw_hands(t_all_data *all_data)
{
	static int		frame_counter = 0;
	static int		hand_frame = 0;
	static int		animation_speed = 8;
	t_mlx_image		*mlx_img;

	if (frame_counter % animation_speed == 0)
	{
		if (all_data->last_hands)
		{
			mlx_delete_image(all_data->mlx, all_data->last_hands);
			all_data->last_hands = NULL;
		}
		mlx_img = mlx_texture_to_image(all_data->mlx, 
				all_data->textures[HANDS1 + hand_frame]);
		if (mlx_img)
		{
			mlx_image_to_window(all_data->mlx, mlx_img, 0, 0);
			all_data->last_hands = mlx_img;
		}
		hand_frame = (hand_frame + 1) % 4;
	}
	frame_counter++;
	if (frame_counter >= animation_speed * 5 * 1000)
		frame_counter = 0;
}

void	render(t_all_data *all_data)
{
	draw_background(all_data);
	draw_walls(all_data);
	draw_minimap(all_data);
	draw_hands(all_data);
}
