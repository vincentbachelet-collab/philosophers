/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create_and_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:58:21 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/10 15:48:36 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	left_right_fork_init(t_root *infos, int i)
{
	if (infos->philo[i].id != 1)
		infos->philo[i].fork_left_hand = infos->philo[i].id;
	else if (infos->philo[i].id == 1)
		infos->philo[i].fork_left_hand = infos->number_of_philosophers;
	if (infos->philo[i].id != 1)
		infos->philo[i].fork_right_hand = infos->philo[i].id - 1;
	else if (infos->philo[i].id == 1)
		infos->philo[i].fork_right_hand = 1;
}

int	p_thread_join(t_root *infos)
{
	int	i;

	i = 0;
	while (i++ < infos->number_of_philosophers)
	{
		if (pthread_join(infos->philo[i].thread, 0) != 0)
		{
			ft_putendl_fd("Error_pthread_join\n", 2);
			return (1);
		}
	}
	return (0);
}

int	p_thread_create(t_root *infos)
{
	int i;

	i = 0;
	while (i++ < infos->number_of_philosophers)
	{
		infos->philo[i].id = i; // a ne pas init ici 
		left_right_fork_init(infos, i);
		if (pthread_create(&infos->philo[i].thread, NULL, 
			&philo_has_taken_a_fork, &infos->philo[i]) != 0)
		{
			ft_putendl_fd("Error_pthread_create_init\n", 2);
			return (1);
		}
		usleep(infos->time_to_eat);
	}
	return  (0);
}
int	thread_philo_creation(t_root *infos)
{
	if (pthread_mutex_init(infos->fork, NULL) != 0)
	{
		ft_putendl_fd("Error_mutex_init\n", 2);
		free_malloc_and_exit(infos, 1);
	}
	if (p_thread_create(infos) != 0)
		free_malloc_and_exit(infos, 1);
	if (p_thread_join(infos) != 0)
		free_malloc_and_exit(infos, 1);
	pthread_mutex_destroy(infos->fork);
	return (0);
}

