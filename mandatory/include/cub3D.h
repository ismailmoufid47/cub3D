
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

# define TILE 100
# define WIDTH 1000
# define HEIGHT 1000
# define FOV 90
# define N_RAYS 200
# define WALL_HEIGHT 50

# define PI 3.1415926

typedef struct s_player
{
	float		y;
	float		x;
	float		direction;
}				t_player;

typedef struct s_ray
{
	float		start_y;
	float		start_x;
	float		end_x;
	float		end_y;
	float		angle;
}				t_ray;

typedef struct s_all_data
{
	char		**textures_and_colors;
	char		***colors;
	char		**map;
	t_mlx		*mlx;
	t_mlx_image	*image;
	t_player	*player;
	t_ray		*rays;
	int			F_color;
	int			C_color;
	int			textures_fd[4];
}				t_all_data;

typedef enum e_text_col
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	INVALID
}				t_text_col;

// Parse:

int				open_cub_file(char *filename);

// Parse Textures:
char			**get_textures_and_colors(int fd, t_all_data *all_data);
void			get_colors(t_all_data *all_data);

// Parse Map:
char			**get_map(int fd);

// Cast Rays:
void			cast_rays(t_all_data *all_data);

// Utils:

// Parse utils:
char			**get_six_lines(int fd);
char			*get_next_non_empty_line(int fd);
t_text_col		get_text_value(char *s);

// Errors:

// Textures Error:
void			textures_and_colors_error(char ***textures_and_colors);

// map Error:
void			pre_map_error(char **map);

void			draw_map(char **map, t_mlx_image *image);
#endif