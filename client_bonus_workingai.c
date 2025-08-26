/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:52:29 by loasaad           #+#    #+#             */
/*   Updated: 2025/08/26 19:40:02 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t g_ack_received = 0;

static void handler_client(int sig, siginfo_t *info, void *ucontext)
{
    (void)info;
    (void)ucontext;
    
    if (sig == SIGUSR2)
    {
        write(1, "ACK\n", 4); // Debug: show when we get acknowledgment
        g_ack_received = 1;
    }
}

static void client_sigactions(void)
{
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR2);
    
    sa.sa_sigaction = handler_client;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        write(2, "sigaction failed\n", 17);
        exit(1);
    }
}

static int send_bit(pid_t server_pid, int bit)
{
    int attempts = 0;
    
    g_ack_received = 0;
    
    write(1, bit ? "1" : "0", 1); // Debug: show bit being sent
    
    // Send the bit
    if (kill(server_pid, bit ? SIGUSR2 : SIGUSR1) == -1)
    {
        write(2, "Failed to send signal\n", 22);
        return (-1);
    }
    
    // Wait for acknowledgment with timeout
    while (!g_ack_received && attempts < 10000) // Increased timeout
    {
        usleep(10); // Reduced sleep time
        attempts++;
    }
    
    if (!g_ack_received)
    {
        write(2, "\nNo acknowledgment received\n", 28);
        return (-1);
    }
    
    return (0);
}

static int send_char(pid_t server_pid, char c)
{
    int i;
    int bit;
    
    write(1, "\nSending char: ", 15);
    write(1, &c, 1);
    write(1, " (", 2);
    
    i = 7;
    while (i >= 0)
    {
        bit = (c >> i) & 1;
        if (send_bit(server_pid, bit) == -1)
            return (-1);
        i--;
    }
    write(1, ")\n", 2);
    return (0);
}

static int send_string(pid_t server_pid, char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (send_char(server_pid, str[i]) == -1)
            return (-1);
        i++;
    }
    
    write(1, "\nSending null terminator...\n", 28);
    // Send null terminator
    if (send_char(server_pid, '\0') == -1)
        return (-1);
    
    return (0);
}

static int is_valid_pid(char *pid_str)
{
    int i;
    
    i = 0;
    if (!pid_str || !pid_str[0])
        return (0);
    
    while (pid_str[i])
    {
        if (pid_str[i] < '0' || pid_str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    pid_t server_pid;
    
    if (argc != 3)
    {
        write(2, "Usage: ./client <server_pid> <message>\n", 40);
        return (1);
    }
    
    if (!is_valid_pid(argv[1]))
    {
        write(2, "Error: Invalid PID\n", 19);
        return (1);
    }
    
    atoi_safe(argv[1], &server_pid);
    if (server_pid <= 0)
    {
        write(2, "Error: Invalid PID\n", 19);
        return (1);
    }
    
    // Test if server process exists
    if (kill(server_pid, 0) == -1)
    {
        write(2, "Error: Server process not found\n", 33);
        return (1);
    }
    
    write(1, "Setting up signal handling...\n", 31);
    client_sigactions();
    
    write(1, "Starting to send message...\n", 29);
    if (send_string(server_pid, argv[2]) == -1)
    {
        write(2, "Error: Failed to send message\n", 31);
        return (1);
    }
    
    write(1, "Message sent successfully\n", 26);
    return (0);
}

// t_client_state g_client;

// static	void	handler_client(int sig, siginfo_t *info, void *ucontext)
// {
// 	(void)sig;
// 	(void)info;
// 	(void)ucontext;
// 	g_client.ack_flag = 1;
// }

// static void	client_sigactions(void)
// {
// 	struct sigaction sa;
	
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_sigaction = handler_client;
// 	sa.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGUSR1, &sa, NULL) == -1)
// 		exit(1);
// }


// static void send_char(pid_t pid, unsigned char c)
// {
// 	int	i;
// 	int pos;
	
// 	i = 0;
// 	while (i < 8)
// 	{
// 		pos = 7 - i;
// 		g_client.ack_flag = 0;
// 		if (c & (1 << pos))
// 			kill (pid, SIGUSR2);
// 		else
// 			kill (pid, SIGUSR1);
// 		while (!g_client.ack_flag)
// 			usleep(50);
// 		i++;
// 	}
// }

// static void send_str(pid_t pid, unsigned char *str)
// {
// 	while (*str)
// 	{
// 		send_char(pid, *str);
// 		str++;
// 	}
// 	send_char(pid, 0);
// }

// int	main(int argc, char **argv)
// {
// 	int				temp;
// 	pid_t			pid;
// 	unsigned char	*str;
	
// 	if (argc != 3 || !atoi_safe(argv[1], &temp) || temp <= 0)
// 		exit(1);
// 	pid = (pid_t)temp;
// 	if (kill(pid, 0) == -1)
// 		exit (1);
// 	client_sigactions();
// 	str = (unsigned char *)argv[2];
// 	send_str(pid, str);
// 	return (0);
// }