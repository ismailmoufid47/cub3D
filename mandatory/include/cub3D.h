
#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef enum e_text_col
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	INVALID
}	t_text_col;

// Parse:

void		parse_cub_file(char *filename);

// Parse Textures:
char		**get_textures_and_colors(int fd);

// Parse Map:
char		**get_map(int fd);

//Utils:

// Parse utils:
char		*get_next_non_empty_line(int fd);

//Errors:

// map Error:
void		pre_map_error(char **map);

#endif