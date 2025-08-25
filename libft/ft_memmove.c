/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:48:16 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/21 11:44:30 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr_d;
	const unsigned char	*ptr_s;

	if (dest == NULL && src == NULL && n == 0)
		return (NULL);
	ptr_d = (unsigned char *)dest;
	ptr_s = (const unsigned char *)src;
	if (ptr_d > ptr_s && ptr_d < ptr_s + n)
	{
		i = n;
		while (i-- > 0)
			ptr_d[i] = ptr_s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			ptr_d[i] = ptr_s[i];
			i++;
		}
	}
	return (dest);
}
