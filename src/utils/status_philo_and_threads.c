/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:52:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/14 15:50:12 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_is_eating(t_philo *philo)
{
	
	pthread_mutex_lock(&philo->root->fork[philo->fork_left_hand]);
	pthread_mutex_lock(&philo->root->fork[philo->fork_right_hand]);
	gettimeofday(&philo->end, 0);
	usleep(philo->time_to_eat);
	printf("philo %d has taken the right fork number %d\n", philo->id,
		philo->fork_right_hand);
	printf("philo %d has taken the left fork number %d\n",
		philo->id, philo->fork_left_hand);
	// printf("%ld ms: philo %d has taken a fork\n", philo->end.tv_usec - philo->start.tv_usec, philo->id);
	printf("%ld ms: philo %d is eating\n", (philo->end.tv_sec * 1000 + philo->end.tv_usec / 1000) \
	- (philo->start.tv_sec * 1000 + philo->start.tv_usec / 1000), philo->id);
	usleep(philo->time_to_eat);
	philo->has_eaten++;
	if (check_if_number_of_has_been_eaten(philo) == TRUE)
	{
		printf("EVERYONE IS FED, congratulations\n"); // ne pas oublier de break ou free ici
		{
			pthread_mutex_destroy(philo->root->fork);
			pthread_mutex_destroy(philo->root->sleep);
			exit(0);
		}
	}
	pthread_mutex_unlock(&philo->root->fork[philo->fork_right_hand]);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_left_hand]);
	return (0);
}

void	*philo_is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->sleep[philo->id]);
	gettimeofday(&philo->end, 0);
	usleep(philo->time_to_sleep);
	printf("%ld ms: philo %d is sleeping\n", (philo->end.tv_sec * 1000 + philo->end.tv_usec / 1000) \
	- (philo->start.tv_sec * 1000 + philo->start.tv_usec / 1000), philo->id);
	pthread_mutex_unlock(&philo->root->sleep[philo->id]);
	return (0);
}

void	*philo_has_taken_a_fork(void *arg)
{
	t_philo	*philo;
	// int i;

	// i = 0;
	philo = ((t_philo *)arg);
	philo->root = (t_root *)malloc(sizeof(t_root));
	while (1) // rajouter condition tant que philo non mort
	{
		if (philo->id % 2 == 0)
			usleep(50000);
		check_if_philo_is_dead(philo);
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		gettimeofday(&philo->end, 0);
		printf("%ld ms: philo %d is thinking\n", (philo->end.tv_sec * 1000 + philo->end.tv_usec / 1000) \
		- (philo->start.tv_sec * 1000 + philo->start.tv_usec / 1000), philo->id);
	}
	if (philo->root)
		free(philo->root);
	return (0);
}
