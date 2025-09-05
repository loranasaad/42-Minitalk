/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:23:42 by loasaad           #+#    #+#             */
/*   Updated: 2025/09/05 13:31:09 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

static	int	skip_space_sign(const char *str, int *i)
{
	int	sign;

	while ((str[*i] <= 13 && str[*i] >= 9) || str[*i] == ' ')
		(*i)++;
	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	atoi_safe(const char *str, int *result)
{
	int		i;
	int		sign;
	long	numb;

	i = 0;
	numb = 0;
	sign = skip_space_sign(str, &i);
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		numb = (str[i] - '0') + (10 * numb);
		if ((sign == 1 && numb > INT_MAX) || (sign == -1 && - numb < INT_MIN))
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	*result = (int)(sign * numb);
	return (1);
}
