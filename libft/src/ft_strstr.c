/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:52:03 by isel-mou          #+#    #+#             */
/*   Updated: 2025/07/16 13:13:29 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//segfaults in case of passing null pointer as haystack
char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	haystack_index;
	size_t	match_count;

	if (!haystack)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	haystack_index = 0;
	while (haystack[haystack_index])
	{
		match_count = 0;
		while (needle[match_count]
			&& haystack[haystack_index + match_count] == needle[match_count])
			match_count++;
		if (!needle[match_count])
			return ((char *)&haystack[haystack_index]);
		haystack_index++;
	}
	return (NULL);
}
