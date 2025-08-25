/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:31:56 by loasaad           #+#    #+#             */
/*   Updated: 2025/08/25 14:11:25 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H	

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"

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

extern	t_server_state	g_server;
extern	t_client_state	g_client;	

#endif