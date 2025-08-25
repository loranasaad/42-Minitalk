/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:37:57 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/20 16:56:09 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_joined;
	int		s1_len;
	int		s2_len;
	int		total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	str_joined = (char *) malloc (total_len);
	if (!str_joined)
		return (NULL);
	ft_strlcpy(str_joined, s1, total_len);
	ft_strlcat(str_joined, s2, total_len);
	return (str_joined);
}
