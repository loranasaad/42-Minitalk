/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:52:29 by loasaad           #+#    #+#             */
/*   Updated: 2025/08/25 18:12:40 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_char(int pid, char c)
{
	int	i;
	int pos;
	
	i = 0;
	while(i < 8)
	{
		
	}
}

void send_str(int pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	return;
}

int	main (int argc, char **argv)
{
	int	pid;
	
	if (argc != 3)
		exit(1);
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) == -1)
		exit (1);
	send_str(pid, argv[2]);
	return (0);
}