/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:12:12 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/14 18:10:51 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*latest = NULL;

	while (*s)
	{
		if (*s == (char) c)
			latest = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *) latest);
}
