/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:52:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/15 12:56:59 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_current_time(t_philo *philo)
{
	int current_time;
	
	gettimeofday(&philo->root->end, 0);
	current_time = (philo->root->end.tv_sec * 1000
		+ philo->root->end.tv_usec / 1000) \
		- (philo->root->start.tv_sec * 1000 + philo->root->start.tv_usec / 1000);
	return (current_time);
}

int	philo_is_eating(t_philo *philo)
{
	
	int current_time;
	
	pthread_mutex_lock(&philo->root->fork[philo->fork_left_hand]);
	pthread_mutex_lock(&philo->root->fork[philo->fork_right_hand]);
	current_time = get_current_time(philo);
	printf("%d ms: philo %d has taken a fork %d\n",
		current_time, philo->id, philo->fork_right_hand);
	printf("%d ms: philo %d has taken a fork %d\n",
		current_time, philo->id, philo->fork_left_hand);
	printf("%d ms: philo %d is eating\n", current_time, philo->id);
	usleep(philo->root->time_to_eat);
	philo->has_eaten++;
	// if (check_if_number_of_has_been_eaten(philo) == TRUE)
	// {
	// 	printf("EVERYONE IS FED, congratulations\n"); // ne pas oublier de break ou free ici
	// 	return (1);
	// }
	pthread_mutex_unlock(&philo->root->fork[philo->fork_right_hand]);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_left_hand]);
	return (0);
}

void	*philo_is_sleeping(t_philo *philo)
{
	int current_time;

	pthread_mutex_lock(&philo->root->sleep[philo->id]);
	current_time = get_current_time(philo);
	printf("%d ms: philo %d is sleeping\n", current_time, philo->id);
	usleep(philo->root->time_to_sleep);
	pthread_mutex_unlock(&philo->root->sleep[philo->id]);
	return (0);
}

void	*philo_has_taken_a_fork(void *arg)
{
	t_philo	*philo;
	int		current_time;

	philo = ((t_philo *)arg);
	if (philo->root->time_to_die < philo->root->time_to_eat)
	{
		printf("%d ms: philo %d is DEAD\n", get_current_time(philo), philo->id);
		exit (1);
	}
	while (1) // rajouter condition tant que philo non mort
	{
		if (philo->id % 2 == 0)
			usleep(5000);
		philo_is_eating(philo);
		if (check_if_number_of_has_been_eaten(philo) == TRUE)
			return (0);
		philo_is_sleeping(philo);
		current_time = get_current_time(philo);
		printf("%d ms: philo %d is thinking\n", current_time, philo->id);
		if (philo->has_eaten == philo->root->number_of_times_each_philosopher_must_eat)
			return (0);
	}
	return (0);
}
