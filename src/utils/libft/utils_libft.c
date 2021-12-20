/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:50:26 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/19 17:12:48 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write (fd, "\n", 1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static	int	ft_is_space(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int						sign;
	unsigned long long int	nb;

	nb = 0;
	sign = 1;
	while (ft_is_space(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		nb = nb * 10 + *nptr - 48;
		nptr++;
	}
	if (nb > 9223372036854775807 && sign == 1)
		return (-1);
	else if (nb > 9223372036854775807 && sign == -1)
		return (0);
	return (nb * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (s && *s)
		write(fd, s++, 1);
}
