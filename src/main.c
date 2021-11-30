/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:55:25 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 17:49:58 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int	fork;
	fork = 0;
	fork = *(int *)arg;
	pthread_mutex_lock(arg);
	printf ("i = %d\n", fork);
	free(arg);
	pthread_mutex_unlock(arg);
	return (arg);
}

int	thread_philo_creation(t_root *infos)
{;
	pthread_t		th[infos->number_of_philosophers];
	int				i;
	pthread_mutex_t *mutex_fork;
	int				*a;
	
	i = 0;
	// mutex_fork = malloc(sizeof(int));
	// mutex_fork = infos->number_of_philosophers;
	mutex_fork = NULL;
	// pthread_mutex_init(mutex_fork, NULL);
	while (i < infos->number_of_philosophers)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(th + i, NULL, &routine, a)  != 0)
		{
			printf ("Error\n");
			return (i);
		}
		i++;
	}
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_join(th[i], 0) != 0)
		{
			printf ("Error\n");
			return (i);
		}
		i++;
	}
	// pthread_mutex_destroy(mutex_fork);
	return (0);
}

int	init_infos_philo(t_root *infos, char **argv)
{
	if ((infos->number_of_philosophers = ft_atoi(argv[1])) < 1)
		ft_putendl_fd("philophers can't be less than one", 2);
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

int main (int argc, char **argv)
{
	t_root	infos[1];
	struct timeval start;
	struct timeval end;
	
	memset(&infos, 0, sizeof infos);
	if (gettimeofday(&start, 0) < 0)
	{
		printf("error\n");
		exit (1);
	}
	if (argc == 6)
	{
		errors_start_handling(infos, argv);
		init_infos_philo(infos, argv);
		thread_philo_creation(infos);
	}
	else
		ft_putendl_fd("Wrong number of arguments, it sould be 4.\n"
		"1.number_of_philosophers| 2.time_to_die |3.time_to_eat |4.time_to_sleep"
		"| 5.[number_of_times_each_philosopher_must_eat]\n", 2);
	gettimeofday(&end, 0);
	printf("temps total ecoule en ms == %ld ms\n", end.tv_usec - start.tv_usec);
	return (0);
}