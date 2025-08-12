/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cub3D_bonus.h                                                            */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:35:24 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 18:25:12 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

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
# define KEY_ROTATION_SPEED 0.1
# define MOUSE_ROTATION_SPEED 0.05
# define MINIMAP_RADIUS 4
# define MINIMAP_SIZE 20

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
	bool			mouse_moved_left;
	bool			mouse_moved_right;
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
	t_mlx_image		*window_image;
	uint32_t		*window_pixels;
	t_player		*player;
	t_input_state	*input_state;
	t_ray			*rays;
	t_mlx_texture	*textures[24];
	t_mlx_image		*last_hands;
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
	HANDS6,
	HANDS7,
	HANDS8,
	HANDS9,
	HANDS10,
	HANDS11,
	HANDS12,
	HANDS13,
	HANDS14,
	HANDS15,
	HANDS16,
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

/*									Parse:									  */

t_all_data			*init_all_data(char *filename);
/*																			  */
/*							Parse Textures and Colors:						  */
char				**get_textures_and_colors(int fd, t_all_data *all_data);
/*																			  */
/*									Parse Map:								  */
char				**get_map(int fd);
/*																			  */
/*																			  */

/*								 	 Cast Rays:								  */

void				cast_rays(t_all_data *all_data);
/*																			  */
/*																			  */

/*									Render:									  */

void				render(t_all_data *all_data);
/*																			  */
/*																			  */

/*									Handle Input:							  */

void				init_input_state(t_all_data *all_data);
void				game_loop(void *all_dat);
void				key_press_hook(t_mlx_key_data keydata, void *all_dat);
void				mouse_move_hook(double xpos, double ypos, void *all_dat);
/*																			  */
/*																			  */

/*									Utils:									  */

/*									Parse Utils:							  */
char				**get_sixteen_lines(int fd);
char				*get_next_non_empty_line(int fd);
t_texture_type		get_texture_type(char *s);
void				remove_newline(char *line);

/*									Ray Casting Utils:						  */
void				init_ray_cast_data(t_all_data *all, t_ray_cast_data *cast,
						t_ray *ray, int screen_x);
/*																			  */
/*									Render Utils:							  */
void				draw_minimap(t_all_data *all_data);
void				draw_background(t_all_data *all_data);
int					get_wall_type(t_ray *ray);
double				calculate_hit_offset(t_ray *ray, int wall_type);
void				calculate_wall_bounds(double dis, int *starty, int *endy);
int					get_texture_x(double hit_offset, t_mlx_texture *texture);
int					get_map_height(char **map);
int					get_map_width(char *row);

/*																			  */
/*									Input Utils:							  */
void				toggle_doors_in_proximity(t_all_data *all_data);
/*																			  */
/*																			  */

/*									Errors:									  */

/*									MLX Init Error:							  */
void				mlx_init_error(t_all_data *all_data);
/*																			  */
/*									Parse Error:							  */
void				textures_error(char **textures_and_colors, int fd);
/*																			  */
/*																			  */

/*									Free Data:								  */

void				free_all_data(t_all_data *all_data);

#endif