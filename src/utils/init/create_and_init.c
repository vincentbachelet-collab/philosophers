/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:57:30 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/20 14:25:16 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_thread_join(t_root *infos)
{
	int	i;

	i = 0;
	while (++i <= infos->number_of_philosophers)
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
	int	i;

	i = 0;
	while (++i <= infos->number_of_philosophers)
	{
		if (pthread_create(&infos->philo[i].thread, NULL,
				&philo_has_taken_a_fork, &infos->philo[i]) != 0)
		{
			ft_putendl_fd("Error_pthread_create_init\n", 2);
			return (1);
		}
	}
	i = 0;
	while (1)
	{
		i = 0;
		usleep(5000);
		while (++i <= infos->number_of_philosophers)
		{
			if ((check_if_philo_is_dead(infos, i) == 1))
				return (0);
		}
		usleep(500);
	}
	return (0);
}

void	philo_left_right_fork_init(t_root *infos)
{
	int	i;

	i = 0;
	while (++i <= infos->number_of_philosophers)
	{
		infos->philo[i].id = i;
		if (infos->philo[i].id != 1)
			infos->philo[i].fork_left_hand = infos->philo[i].id;
		else if (infos->philo[i].id == 1)
			infos->philo[i].fork_left_hand = infos->number_of_philosophers;
		if (infos->philo[i].id != 1)
			infos->philo[i].fork_right_hand = infos->philo[i].id - 1;
		else if (infos->philo[i].id == 1)
			infos->philo[i].fork_right_hand = 1;
		infos->philo[i].has_eaten = 0;
		infos->philo[i].last_meal = 0;
		infos->philo[i].is_eating = 0;
		infos->philo[i].root = infos;
	}
}

int	p_thread_create_join(t_root *infos)
{
	philo_left_right_fork_init(infos);
	if (p_thread_create(infos) == 1)
		free_malloc_and_exit(infos, 1);
	if (p_thread_join(infos) != 0)
		free_malloc_and_exit(infos, 1);
	return (0);
}

int	thread_philo_creation(t_root *infos)
{
	if (pthread_mutex_init(infos->sleep, NULL) != 0
		|| pthread_mutex_init(&infos->death, NULL) != 0
		|| pthread_mutex_init(infos->fork, NULL) != 0
		|| pthread_mutex_init(&infos->is_eating, NULL) != 0
		|| pthread_mutex_init(&infos->last_meal, NULL) != 0
		|| pthread_mutex_init(&infos->has_eaten, NULL) != 0
		|| pthread_mutex_init(&infos->blabla, NULL) != 0
		|| pthread_mutex_init(&infos->all_meals_eaten, NULL) != 0)
	{
		ft_putendl_fd("Error_mutex_init\n", 2);
		free_malloc_and_exit(infos, 1);
	}
	if (p_thread_create_join(infos) == 1)
		free_malloc_and_exit(infos, 1);
	pthread_mutex_destroy(infos->fork);
	pthread_mutex_destroy(infos->sleep);
	pthread_mutex_destroy(&infos->death);
	pthread_mutex_destroy(&infos->last_meal);
	pthread_mutex_destroy(&infos->is_eating);
	pthread_mutex_destroy(&infos->has_eaten);
	pthread_mutex_destroy(&infos->blabla);
	pthread_mutex_destroy(&infos->all_meals_eaten);
	return (0);
}
