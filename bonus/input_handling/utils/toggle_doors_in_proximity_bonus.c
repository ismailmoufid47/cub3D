/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_doors_in_proximity_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-amr <moel-amr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:35:38 by moel-amr          #+#    #+#             */
/*   Updated: 2025/08/07 12:35:38 by moel-amr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

bool	is_door_in_proximity(t_all_data *all_data, int door_x, int door_y)
{
	int	player_x;
	int	player_y;

	player_x = (int)all_data->player->x;
	player_y = (int)all_data->player->y;
	if ((door_x == player_x && door_y == player_y)
		|| (door_x == player_x - 1 && door_y == player_y)
		|| (door_x == player_x + 1 && door_y == player_y)
		|| (door_x == player_x && door_y == player_y - 1)
		|| (door_x == player_x && door_y == player_y + 1)
		|| (door_x == player_x - 2 && door_y == player_y)
		|| (door_x == player_x + 2 && door_y == player_y)
		|| (door_x == player_x && door_y == player_y - 2)
		|| (door_x == player_x && door_y == player_y + 2))
		return (true);
	return (false);
}

void	toggle_doors_in_proximity(t_all_data *all_data)
{
	int	y;
	int	x;

	y = 0;
	while (all_data->map[y])
	{
		x = 0;
		while (all_data->map[y][x])
		{
			if (all_data->map[y][x] == 'D' || all_data->map[y][x] == 'C')
			{
				if (is_door_in_proximity(all_data, x, y))
					all_data->map[y][x] = 'C';
				else
					all_data->map[y][x] = 'D';
			}
			x++;
		}
		y++;
	}
}
