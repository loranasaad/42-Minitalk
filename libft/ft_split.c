/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:40:53 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/19 16:08:58 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_cntr(const char *str, char c)
{
	int	i;
	int	is_anewword;
	int	word_cnt;

	is_anewword = 1;
	i = 0;
	word_cnt = 0;
	while (str[i])
	{
		if (str[i] == c)
			is_anewword = 1;
		if (is_anewword && str[i] != c)
		{
			word_cnt++;
			is_anewword = 0;
		}
		i++;
	}
	return (word_cnt);
}

static char	*ft_dup(const char *s1, size_t len)
{
	size_t	i;
	char	*s2; 

	s2 = (char *) malloc (len +1);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static int	ft_build_word(const char *s, char **result, size_t word_idx, char c)
{
	size_t	word_len;

	word_len = 0;
	while (s[word_len] && s[word_len] != c)
		word_len++;
	result[word_idx] = ft_dup(s, word_len);
	if (!result[word_idx])
	{
		while (word_idx > 0)
		{
			free(result[word_idx - 1]);
			word_idx--;
		}
		free(result);
		return (0);
	}
	return (word_len);
}

static int	ft_build_array(char const *s, char **result, char c)
{
	size_t		i;
	size_t		word_idx;
	size_t		word_len;

	i = 0;
	word_idx = 0;
	word_len = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			word_len = ft_build_word(&s[i], result, word_idx, c);
			if (word_len == 0)
				return (0);
			word_idx++;
			i += word_len;
		}
	}
	result[word_idx] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	int			word_cnt;

	word_cnt = ft_word_cntr(s, c);
	arr = (char **) malloc ((word_cnt + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!ft_build_array(s, arr, c))
		return (NULL);
	return (arr);
}
