
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
char		**get_map(int fd);
void		parse_cub_file(char *filename);

// Parse Textures:
char		**get_sorted_files(char ***textures_and_colors);
char		**get_textures_and_colors(char ***textures_and_colors);
char		***validate_text_col(char **lines);

// Parse Textures utils:
int			open_cub_file(char *filename);
char		*get_next_line2(int fd);
char		**get_six_lines(int fd);
t_text_col	get_text_value(char *s);

#endif