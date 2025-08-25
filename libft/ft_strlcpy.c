/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:29:39 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/20 15:38:47 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dst_size)
{
	size_t	i;
	size_t	src_length;

	if (!src || !dest)
		return (0);
	src_length = 0;
	while (src[src_length])
		src_length++;
	if (dst_size == 0)
		return (src_length);
	i = 0;
	while (src[i] && i < dst_size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_length);
}
