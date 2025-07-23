#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 960
# define HEIGHT 540
# define WALL_HEIGHT 0.5
# define MOVEMENT_SPEED 0.08
# define ROTATION_SPEED 0.1

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

typedef struct s_ray
{
	double			start_y;
	double			start_x;
	double			end_x;
	double			end_y;
	double			angle;
	t_hit_type		hit_type;
}					t_ray;

typedef struct s_all_data
{
	char			**textures_and_colors;
	char			***colors;
	char			**map;
	t_mlx			*mlx;
	uint32_t		*window_pixels;
	t_mlx_texture	*textures[4];
	t_player		*player;
	t_ray			*rays;
	int				ceiling_color;
	int				floor_color;
}					t_all_data;

typedef enum e_text_col
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	INVALID
}					t_text_col;

typedef struct s_ray_cast_data
{
	double	x_ray_direction;
	double	y_ray_direction;
	double	delta_x;
	double	delta_y;
	double	ray_distance_x;
	double	ray_distance_y;
	double	distance_to_wall;
	int		map_x;
	int		map_y;
}	t_ray_cast_data;

typedef struct s_wall_render_params
{
	int		start_y;
	int		end_y;
	double	distance;
	int		tex_x;
	int		texture_width;
	int		texture_height;
}	t_wall_render_params;

// Parse:
t_all_data		*init_all_data(char *filename);

// Parse Textures:
char			**get_textures_and_colors(int fd, t_all_data *all_data);
// Parse Map:
char			**get_map(int fd);

// Cast Rays:
void			cast_rays(t_all_data *all_data);

// Render:
void			ft_cub3d(t_all_data *all_data);

// Utils:

// Parsing utils:
char			**get_six_lines(int fd);
char			*get_next_non_empty_line(int fd);
t_text_col		get_text_value(char *s);

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

// Errors:

// Textures Error:
void			pre_textures_and_colors_error(char ***textures_and_colors);
void			post_textures_and_colors_error(char **textures_and_colors);

void			draw_map(char **map, t_mlx_image *image); // to remove in madatory
#endif