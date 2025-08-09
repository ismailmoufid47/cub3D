/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cub3D.c                                                                  */
/*                                                 isel-mou@student.1337.ma   */
/*   By: moel-amr & isel-mou                       moel-amr@student.1337.ma   */
/*                                                                            */
/*   Created: 2025/08/07 12:33:24 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:33:24 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

int	main(int argc, char **argv)
{
	t_all_data	*all_data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (EXIT_FAILURE);
	}
	all_data = init_all_data(argv[1]);
	mlx_key_hook(all_data->mlx, key_press_hook, (void *)all_data);
	mlx_loop_hook(all_data->mlx, game_loop, (void *)all_data);
	cast_rays(all_data);
	render(all_data);
	mlx_loop(all_data->mlx);
	mlx_terminate(all_data->mlx);
	free_all_data(all_data);
}
