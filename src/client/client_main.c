/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:52:29 by loasaad           #+#    #+#             */
/*   Updated: 2025/09/05 13:31:47 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_char(pid_t pid, unsigned char c)
{
	int	i;
	int	pos;

	i = 0;
	while (i < 8)
	{
		pos = 7 - i;
		if (c & (1 << pos))
			kill (pid, SIGUSR2);
		else
			kill (pid, SIGUSR1);
		usleep(100);
		i++;
	}
}

static void	send_str(pid_t pid, unsigned char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, 0);
}

int	main(int argc, char **argv)
{
	int				temp;
	pid_t			pid;
	unsigned char	*str;

	if (argc != 3 || !atoi_safe(argv[1], &temp) || temp <= 0)
		exit(1);
	pid = (pid_t)temp;
	if (kill(pid, 0) == -1)
		exit (1);
	str = (unsigned char *)argv[2];
	send_str(pid, str);
	return (0);
}
