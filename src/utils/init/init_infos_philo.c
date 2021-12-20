/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infos_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:52:52 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/20 15:25:15 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display_error_max_meals(t_root *infos, int i, char *argv, int argc)
{
	if (i == 5)
	{
		if (argc == 6)
		{
			infos->number_of_times_each_philosopher_must_eat = ft_atoi(argv);
			if (infos->number_of_times_each_philosopher_must_eat == 0)
			{
				ft_putendl_fd("args can't be zero,", 2);
				return (1);
			}
			else if (infos->number_of_times_each_philosopher_must_eat < 0)
			{
				ft_putendl_fd("args can't be negative", 2);
				return (1);
			}
		}
		else
			infos->number_of_times_each_philosopher_must_eat = -1;
	}
	return (0);
}

int	display_error_eat_sleep(t_root *infos, int i, char *argv)
{
	if (i == 3)
	{
		infos->time_to_eat = ft_atoi(argv) * 1000;
		if (infos->time_to_eat < 0)
		{
			ft_putendl_fd("args can't be negative", 2);
			return (1);
		}
	}
	if (i == 4)
	{
		infos->time_to_sleep = ft_atoi(argv) * 1000;
		if (infos->time_to_sleep <= 0)
		{
			ft_putendl_fd("args can't be negative or zero", 2);
			return (1);
		}
	}
	return (0);
}

int	display_error(t_root *infos, int i, char *argv)
{
	if (i == 1)
	{
		infos->number_of_philosophers = ft_atoi(argv);
		if (infos->number_of_philosophers < 1)
		{
			ft_putendl_fd("philophers can't be less than one", 2);
			return (1);
		}
		if (infos->number_of_philosophers >= 200)
		{
			ft_putendl_fd("philophers can't be more than 200", 2);
			return (1);
		}
	}
	if (i == 2)
	{
		infos->time_to_die = ft_atoi(argv) * 1;
		if (infos->time_to_die <= 0)
		{
			ft_putendl_fd("args can't be negative or zero", 2);
			return (1);
		}
	}
	return (0);
}

int	init_infos_philo(t_root *infos, char **argv, int argc)
{
	if (display_error(infos, 1, argv[1]) == 1)
		return (1);
	if (display_error(infos, 2, argv[2]) == 1)
		return (1);
	if (display_error_eat_sleep(infos, 3, argv[3]) == 1)
		return (1);
	if (display_error_eat_sleep(infos, 4, argv[4]) == 1)
		return (1);
	if (display_error_max_meals(infos, 5, argv[5], argc) == 1)
		return (1);
	gettimeofday(&infos->start, 0);
	return (0);
}
