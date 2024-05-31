/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:01:58 by alemsafi          #+#    #+#             */
/*   Updated: 2023/03/19 17:09:07 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	long	i;
	int		sign;
	long	acc;
	long	start;

	i = 0;
	sign = 1;
	acc = 0;
	while (str[i] && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	start = i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		acc = acc * 10 + (str[i++] - '0');
	if (i - start >= 19)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (acc * sign);
}
