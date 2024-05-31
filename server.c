/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:57:06 by alemsafi          #+#    #+#             */
/*   Updated: 2023/03/31 23:36:07 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		ft_putchar_fd('-', fd);
	}
	else
		nb = n;
	if (nb < 10)
		ft_putchar_fd(nb + '0', fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	chr = '\0';
	static int				bit = 7;
	static int				pid = 0;

	(void)context;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		chr = '\0';
		bit = 7;
	}
	if (signal == SIGUSR1)
		chr |= 1;
	else
		chr |= 0;
	if (bit > 0 && bit--)
		chr = chr << 1;
	else if (chr == '\0')
		kill(pid, SIGUSR2);
	else
	{
		write(1, &chr, 1);
		bit = 7;
		chr = '\0';
	}
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	write(1, "Server ID: ", 11);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
