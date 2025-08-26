/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:31:11 by loasaad           #+#    #+#             */
/*   Updated: 2025/08/26 21:55:59 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_server_state g_server;

static	void	init_server_state(void)
{
	g_server.current_byte = 0;
	g_server.bit_index = 0;
}

static	void	handler_server(int sig, siginfo_t *info, void *ucontext)
{
	int	pos;

	(void)ucontext;
	if (sig == SIGUSR1)
		g_server.bit_index++;
	else if (sig == SIGUSR2)
	{
		pos = 7 - g_server.bit_index;
		g_server.current_byte |= (1 << pos);
		g_server.bit_index++;
	}
	if (info && info->si_pid > 0)
		kill(info->si_pid, SIGUSR1);
	if (g_server.bit_index == 8)
	{
		if (g_server.current_byte == 0)
			write(1, "\n", 1);
		else
			write(1, &g_server.current_byte, 1);
		g_server.bit_index = 0;
		g_server.current_byte = 0;
	}
}
static	void	server_sigactions(void)
{
	struct sigaction sa;
	int	rc1;
	int	rc2;
	
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = handler_server;
	sa.sa_flags = SA_SIGINFO;
	
	rc1 = sigaction(SIGUSR1, &sa, NULL);
	rc2 = sigaction(SIGUSR2, &sa, NULL);

	if (rc1 == -1 || rc2 == -1)
	{
		write(2, "sigaction failed\n", 17);
		exit(1);
	}
}
int	main(void)
{
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	init_server_state();
	server_sigactions();
	
	while (1)
	{
		pause();
	}
	return (0);
}