/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:38:09 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/14 18:04:41 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;
	size_t	dest_length;

	src_length = 0;
	while (src[src_length])
		src_length++;
	dest_length = 0;
	while (dest[dest_length])
		dest_length++;
	if (size <= dest_length)
		return (size + src_length);
	i = 0;
	while (src[i] && i + dest_length < size - 1)
	{
		dest[dest_length + i] = src[i];
		i++;
	}
	dest[dest_length + i] = '\0';
	return (dest_length + src_length);
}
