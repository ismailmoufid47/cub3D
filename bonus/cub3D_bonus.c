/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cub3D_bonus.c                                                            */
/*                                                 isel-mou@student.1337.ma   */
/*   By: moel-amr & isel-mou                       moel-amr@student.1337.ma   */
/*                                                                            */
/*   Created: 2025/08/07 12:36:42 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 18:24:19 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D_bonus.h"

int check_fd_leaks(void)
{
	int fd_count = 0;
	for (int fd = 3; fd < 1024; fd++) {
		if (fcntl(fd, F_GETFD) != -1) {
			char path[PATH_MAX];
			char fd_path[64];
			snprintf(fd_path, sizeof(fd_path), "/dev/fd/%d", fd);
			
			ssize_t len = readlink(fd_path, path, sizeof(path) - 1);
			if (len != -1) {
				path[len] = '\0';
				if (ft_strstr(path, "/System/Library/") ||
					ft_strstr(path, "/private/var/folders/") ||
					ft_strstr(path, "com.apple.metal") ||
					ft_strstr(path, "CoreImage.framework")) {
					continue;
				}
				fd_count++;
			}
		}
	}
	return fd_count > 0;
}

int	check_memory_leaks(void)
{
	int	ret;
	ret = system("leaks -q cub3D");
	return (ret != 0);
}

void check_fd_and_memory_leaks(void)
{
	if (check_fd_leaks())
	{
		ft_putendl_fd("Error: File descriptor leaks detected.", 2);
		char cmd[256];
		snprintf(cmd, sizeof(cmd), "lsof -p %d", getpid());
		if (system(cmd) == -1)
			ft_putendl_fd("Failed to run lsof command.", 2);
		exit(EXIT_FAILURE);
	}
	if (check_memory_leaks())
	{
		ft_putendl_fd("Error: Memory leaks detected.", 2);
		exit(EXIT_FAILURE);
	}
}
int	main(int argc, char **argv)
{
	t_all_data	*all_data;

	atexit(check_fd_and_memory_leaks);
	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (EXIT_FAILURE);
	}
	all_data = init_all_data(argv[1]);
	mlx_set_cursor_mode(all_data->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(all_data->mlx, mouse_move_hook, (void *)all_data);
	mlx_key_hook(all_data->mlx, key_press_hook, (void *)all_data);
	mlx_loop_hook(all_data->mlx, game_loop, (void *)all_data);
	cast_rays(all_data);
	render(all_data);
	mlx_loop(all_data->mlx);
	free_all_data(all_data);
}
