/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:52:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/14 17:17:04 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_current_time(t_philo *philo)
{
	int current_time;
	
	current_time = (philo->root->end.tv_sec * 1000
		+ philo->root->end.tv_usec / 1000) \
		- (philo->root->start.tv_sec * 1000 + philo->root->start.tv_usec / 1000);
	return (current_time);
}

void	*philo_is_eating(t_philo *philo)
{
	
	int current_time;
	
	pthread_mutex_lock(&philo->root->fork[philo->fork_left_hand]);
	pthread_mutex_lock(&philo->root->fork[philo->fork_right_hand]);
	gettimeofday(&philo->root->end, 0);
	current_time = get_current_time(philo);
	printf("%d ms: philo %d has taken a fork %d\n",
		current_time, philo->id, philo->fork_right_hand);
	printf("%d ms: philo %d has taken a fork %d\n",
		current_time, philo->id, philo->fork_left_hand);
	printf("%d ms: philo %d is eating\n", current_time, philo->id);
	usleep(philo->root->time_to_eat);
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
	int current_time;

	pthread_mutex_lock(&philo->root->sleep[philo->id]);
	gettimeofday(&philo->root->end, 0);
	current_time = get_current_time(philo);
	printf("%d ms: philo %d is sleeping\n", current_time, philo->id);
	usleep(philo->root->time_to_sleep);
	pthread_mutex_unlock(&philo->root->sleep[philo->id]);
	return (0);
}

void	*philo_has_taken_a_fork(void *arg)
{
	t_philo	*philo;
	t_root	*infos;
	int		current_time;

	philo = ((t_philo *)arg);
	infos = philo->root;
	while (1) // rajouter condition tant que philo non mort
	{
		if (philo->id % 2 == 0)
			usleep(50000);
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		gettimeofday(&infos->end, 0);
		current_time = get_current_time(philo);
		printf("%d ms: philo %d is thinking\n", current_time, philo->id);
	}
	return (0);
}
