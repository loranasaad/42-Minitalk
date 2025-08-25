#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	handler(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Got SIGUSR1!\n", 13);
	else if (sig == SIGUSR2)
		write(1, "Got SIGUSR2!\n", 13);
}

int	main(void)
{
	printf("My PID is %d\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);

	while (1)
		pause();
}

