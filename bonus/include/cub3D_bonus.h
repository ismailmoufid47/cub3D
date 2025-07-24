#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080
# define MOVEMENT_SPEED 0.08
# define ROTATION_SPEED 0.1

typedef enum e_whats_hit
{
	WALL_HIT,
	DOOR_HIT,
}					t_whats_hit;

typedef enum e_hit_type
{
	HORIZONTAL,
	VERTICAL,
}					t_hit_type;
typedef struct s_player
{
	double			y;
	double			x;
	double			direction;
}					t_player;

typedef struct s_input_state
{
	bool			w_pressed;
	bool			s_pressed;
	bool			a_pressed;
	bool			d_pressed;
	bool			left_pressed;
	bool			right_pressed;
}					t_input_state;

typedef struct s_ray
{
	double			start_y;
	double			start_x;
	double			end_x;
	double			end_y;
	double			angle;
	t_hit_type		hit_type;
	t_whats_hit		whats_hit;
}					t_ray;

typedef struct s_all_data
{
	char			**textures_and_colors;
	char			**map;
	t_mlx			*mlx;
	uint32_t		*window_pixels;
	t_player		*player;
	t_input_state	*input_state;
	t_ray			*rays;
	t_mlx_texture	*textures[10];
	int				ceiling_color;
	int				floor_color;
}					t_all_data;

typedef enum e_text_col
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR,
	HANDS1,
	HANDS2,
	HANDS3,
	HANDS4,
	HANDS5,
	FLOOR,
	CEILING,
	INVALID
}					t_texture_type;

typedef struct s_ray_cast_data
{
	double			x_ray_direction;
	double			y_ray_direction;
	double			delta_x;
	double			delta_y;
	double			ray_distance_x;
	double			ray_distance_y;
	double			distance_to_wall;
	int				map_x;
	int				map_y;
}					t_ray_cast_data;

typedef struct s_wall_render_params
{
	int				start_y;
	int				end_y;
	double			distance;
	int				tex_x;
	int				texture_width;
	int				texture_height;
}					t_wall_render_params;

// Parse:
t_all_data		*init_all_data(char *filename);

// Parse Textures:
char			**get_textures_and_colors(int fd, t_all_data *all_data);
// Parse Map:
char			**get_map(int fd);

// Cast Rays:
void			cast_rays(t_all_data *all_data);

// Render:
void			render(t_all_data *all_data);

// Handle Input:
void			init_input_state(t_all_data *all_data);
void			update_player_movement(void *all_dat);
void			key_press_hook(t_mlx_key_data keydata, void *all_dat);

// Utils:

// Parsing utils:
char			**get_twelve_lines(int fd);
char			*get_next_non_empty_line(int fd);
t_texture_type	get_texture_type(char *s);

// Ray casting utils:
void			init_ray(t_ray *ray, t_player *player, double angle);
void			init_ray_cast_data(t_ray_cast_data *data, t_all_data *all_data,
					double angle);
void			calculate_deltas(t_ray_cast_data *data);

// Rendering utils:
int				get_wall_type(t_ray *ray);
double			calculate_hit_offset(t_ray *ray, int wall_type);
void			calculate_wall_bounds(double dis, int *start_y, int *end_y);
int				get_texture_x(double hit_offset, t_mlx_texture *texture);

// Input handling utils:
void			toggle_doors_in_proximity(t_all_data *all_data);

// Errors:

// Textures Error:
void			pre_textures_and_colors_error(char ***textures_and_colors);
void			post_textures_and_colors_error(char **textures_and_colors);

// Free Resources:

void			free_all_data(t_all_data *all_data);

#endif