/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:31:56 by loasaad           #+#    #+#             */
/*   Updated: 2025/08/26 19:26:16 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H	
# define INT_MAX	2147483647
# define INT_MIN	(-2147483648)

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_server_state
{
	unsigned char	current_byte;
	int				bit_index;
	pid_t			client_pid;
}					t_server_state;

typedef struct s_client_state
{
	volatile	sig_atomic_t	ack_flag;
}								t_client_state;
void	ft_putnbr_fd(int n, int fd);
int		atoi_safe(const char *str, int *result);

extern	t_server_state	g_server;
extern	t_client_state	g_client;	

#endif