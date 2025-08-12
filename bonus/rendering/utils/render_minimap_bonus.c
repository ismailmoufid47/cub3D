/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   render_minimap_bonuns.c                                                  */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:35:48 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:35:48 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	get_map_height(char **map)
{
	static char	**last_map = NULL;
	static int	cached_height = 0;
	int			h;

	if (map != last_map)
	{
		h = 0;
		if (map)
			while (map[h])
				h++;
		cached_height = h;
		last_map = map;
	}
	return (cached_height);
}

int	get_map_width(char *row)
{
	static char	*last_row = NULL;
	static int	cached_width = 0;
	int			width;

	if (row != last_row)
	{
		width = ft_strlen(row);
		cached_width = width;
		last_row = row;
	}
	return (cached_width);
}
