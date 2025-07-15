/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:30:53 by isel-mou          #+#    #+#             */
/*   Updated: 2025/07/15 17:31:15 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	free_splits(char ***splits)
{
	char	***original;

	original = splits;
	while (*splits)
	{
		ft_free_split(*splits);
		splits++;
	}
	free(original);
}
