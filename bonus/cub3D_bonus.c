/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cub3D_bonus.c                                                            */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:36:42 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 18:24:19 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D_bonus.h"

int	main(int argc, char **argv)
{
	t_all_data	*all_data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (EXIT_FAILURE);
	}
	all_data = init_all_data(argv[1]);
	mlx_cursor_hook(all_data->mlx, mouse_move_hook, (void *)all_data);
	mlx_key_hook(all_data->mlx, key_press_hook, (void *)all_data);
	mlx_loop_hook(all_data->mlx, game_loop, (void *)all_data);
	cast_rays(all_data);
	render(all_data);
	mlx_loop(all_data->mlx);
	free_all_data(all_data);
}
