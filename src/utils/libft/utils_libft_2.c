/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:22 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/20 15:47:25 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (n < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	nb = nb % 10 + 48;
	write(fd, &nb, 1);
}

long long int	ft_atol(const char *str)
{
	int					i;
	int					neg;
	long long			num;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (num > 9223372036854775807 && neg == 1)
		return (-1);
	else if (num > 9223372036854775807 && neg == -1)
		return (0);
	return (num * neg);
}
