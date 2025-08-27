/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:52:29 by loasaad           #+#    #+#             */
/*   Updated: 2025/08/27 16:10:57 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_client_state g_client;

static	void	handler_client(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	g_client.ack_flag = 1;
	write(1, " ACK recieved\n", 14);
}

static void	client_sigactions(void)
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask ,SIGUSR1);
	sa.sa_sigaction = handler_client;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(1);
}


static void send_char(pid_t pid, unsigned char c)
{
	int	i;
	int pos;
	
	i = 0;
	write(1, "sending ", 8);
	write(1, &c, 1);
	write(1, "\n", 1); 
	while (i < 8)
	{
		pos = 7 - i;
		g_client.ack_flag = 0;
		if (c & (1 << pos))
			kill (pid, SIGUSR2);
		else
			kill (pid, SIGUSR1);
		write(1, "bit ", 4);
		ft_putnbr_fd(i, 1);
		while (!g_client.ack_flag)
			usleep(10);
		i++;
	}
}

static void send_str(pid_t pid, unsigned char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	write (1, "null terminator ", 16);
	send_char(pid, 0);
}

int	main(int argc, char **argv)
{
	int				temp;
	pid_t			pid;
	unsigned char	*str;
	
	if (argc != 3 || !atoi_safe(argv[1], &temp))
		exit(1);
	pid = (pid_t)temp;
	if (kill(pid, 0) == -1)
		exit (1);
	client_sigactions();
	str = (unsigned char *)argv[2];
	send_str(pid, str);
	return (0);
}