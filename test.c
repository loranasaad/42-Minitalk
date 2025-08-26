
#include "minitalk_bonus.h"

t_server_state g_server;

static void init_server_state(void)
{
    g_server.current_byte = 0;
    g_server.bit_index = 0;
    g_server.client_pid = 0; // Add this to track client PID
}

static void handler_server(int sig, siginfo_t *info, void *ucontext)
{
    (void)ucontext;
    
    // Store client PID on first signal
    if (g_server.client_pid == 0 && info && info->si_pid > 0)
        g_server.client_pid = info->si_pid;
    
    // Only accept signals from the current client
    if (info && info->si_pid != g_server.client_pid)
        return;
    
    if (sig == SIGUSR1)
    {
        // SIGUSR1 = 0 bit, just increment bit_index
        g_server.bit_index++;
    }
    else if (sig == SIGUSR2)
    {
        // SIGUSR2 = 1 bit, set the bit and increment
        int pos = 7 - g_server.bit_index;
        g_server.current_byte |= (1 << pos);
        g_server.bit_index++;
    }
    
    // Send acknowledgment back to client
    if (g_server.client_pid > 0)
    {
        if (kill(g_server.client_pid, SIGUSR2) == -1)
        {
            // If kill fails, reset client connection
            g_server.client_pid = 0;
            g_server.current_byte = 0;
            g_server.bit_index = 0;
            return;
        }
    }
    
    // Check if we received a complete byte (8 bits)
    if (g_server.bit_index == 8)
    {
        if (g_server.current_byte == 0)
        {
            // Null terminator - end of string
            write(1, "\n", 1);
            // Reset for next message
            g_server.client_pid = 0;
        }
        else
        {
            // Regular character
            write(1, &g_server.current_byte, 1);
        }
        
        // Reset for next byte
        g_server.bit_index = 0;
        g_server.current_byte = 0;
    }
}

static void server_sigactions(void)
{
    struct sigaction sa;
    
    // Initialize the sigaction structure
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    
    sa.sa_sigaction = handler_server;
    sa.sa_flags = SA_SIGINFO | SA_RESTART; // Add SA_RESTART
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
        sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        write(2, "sigaction failed\n", 17);
        exit(1);
    }
}

int main(void)
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