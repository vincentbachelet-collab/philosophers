/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_and_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:58:21 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/09 16:27:04 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int	nb_fork;
	
	nb_fork = *(int *)arg;
	pthread_mutex_lock(arg);
	printf ("==> i = %d\n", nb_fork);
	pthread_mutex_unlock(arg);
	return (0);
}

int	p_thread_join(t_root *infos, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_join(th[i], 0) != 0)
		{
			ft_putendl_fd("Error_pthread_join\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	p_thread_create(t_root *infos, pthread_t *th, pthread_mutex_t mutex_fork)
{
	int	i;

	i = 0;
	(void) mutex_fork;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_create(&th[i], NULL, &routine, &mutex_fork) != 0)
		{
			ft_putendl_fd("Error_pthread_create_init\n", 2);
			return (1);
		}
		usleep(40000);
		i++;
	}
	return  (0);
}
int	thread_philo_creation(t_root *infos)
{
	pthread_mutex_t	mutex_fork;
	pthread_t		th[infos->number_of_philosophers];
	
	if (pthread_mutex_init(&mutex_fork, NULL) != 0)
	{
		ft_putendl_fd("Error_mutex_init\n", 2);
		exit (1);
	}
	if (p_thread_create(infos, th, mutex_fork) != 0)
		return (1);
	if (p_thread_join(infos, th) != 0)
		return (1);
	pthread_mutex_destroy(&mutex_fork);
	return (0);
}

int	init_infos_philo(t_root *infos, char **argv)
{
	if ((infos->number_of_philosophers = ft_atoi(argv[1])) < 1)
		ft_putendl_fd("philophers can't be less than one", 2);
	if ((infos->number_of_philosophers = ft_atoi(argv[1])) >= 200)
		ft_putendl_fd("philophers can't be more than 200", 2);
	if ((infos->time_to_die = ft_atoi(argv[2])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	if ((infos->time_to_eat = ft_atoi(argv[3])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	if ((infos->time_to_eat = ft_atoi(argv[4])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	if ((infos->number_of_times_each_philosopher_must_eat = atoi(argv[5])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	return (0);
}
