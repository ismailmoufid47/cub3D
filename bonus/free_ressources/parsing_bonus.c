/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   parsing_bonus.c                                                          */
/*                                                 isel-mou@student.1337.ma   */
/*   By: moel-amr & isel-mou                       moel-amr@student.1337.ma   */
/*                                                                            */
/*   Created: 2025/08/07 12:35:19 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 18:24:33 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	mlx_init_error(t_all_data *all_data)
{
	free(all_data);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

void	textures_error(char **textures_and_colors, int fd)
{
	close(fd);
	ft_free_split(textures_and_colors);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}
