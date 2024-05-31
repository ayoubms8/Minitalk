/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:56:46 by alemsafi          #+#    #+#             */
/*   Updated: 2023/03/31 23:29:09 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

void	handler(int signal)
{
	if (signal == SIGUSR2)
		write(1, "message sent !\n", 16);
}

int	main(int ac, char **av)
{
	int	srvpid;

	signal(SIGUSR2, handler);
	if (ac != 3 || !av[2])
		return (write(1, "invalid arguments !\n", 20), 1);
	srvpid = ft_atoi(av[1]);
	if (srvpid <= 0 || !is_num(av[1]))
		return (write(1, "invalid arguments !\n", 20), 1);
	sned_data(srvpid, (unsigned char *)av[2]);
	return (0);
}

void	sned_data(int srvpid, unsigned char *str)
{
	int	i;
	int	h;

	i = 0;
	while (str[i])
	{
		h = 7;
		while (h >= 0)
		{
			if ((str[i] >> h) & 1)
				kill(srvpid, SIGUSR1);
			else
				kill(srvpid, SIGUSR2);
			usleep(700);
			h--;
		}
		i++;
	}
	i = 8;
	while (i--)
	{
		kill(srvpid, SIGUSR2);
		usleep(700);
	}
}
