/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infos_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:52:52 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/15 12:40:20 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_infos_philo(t_root *infos, char **argv)
{
	infos->number_of_philosophers = ft_atoi(argv[1]);
	if (infos->number_of_philosophers < 1)
		ft_putendl_fd("philophers can't be less than one", 2);
	if (infos->number_of_philosophers >= 200)
		ft_putendl_fd("philophers can't be more than 200", 2);
	infos->time_to_die = ft_atoi(argv[2]) * 1000;
	if (infos->time_to_die < 0)
		ft_putendl_fd("args can't be negative", 2);
	infos->time_to_eat = ft_atoi(argv[3]) * 1000;
	if (infos->time_to_eat < 0)
		ft_putendl_fd("args can't be negative", 2);
	infos->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (infos->time_to_sleep < 0)
		ft_putendl_fd("args can't be negative", 2);
	if (argv[5])
	{
		infos->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
			if (infos->number_of_times_each_philosopher_must_eat < 0)
				ft_putendl_fd("args can't be negative", 2);
	}
	gettimeofday(&infos->start, 0);
	return (0);
}

