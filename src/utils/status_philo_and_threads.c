/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:52:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/13 19:03:41 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->fork[philo->fork_left_hand]);
	pthread_mutex_lock(&philo->root->fork[philo->fork_right_hand]);
	printf("philo %d has taken the right fork number %d\n", philo->id,
		philo->fork_right_hand);
	printf("philo %d has taken the left fork number %d\n",
		philo->id, philo->fork_left_hand);
	printf("philo %d is eating\n", philo->id);
	philo->has_eaten++;
	if (check_if_number_of_has_been_eaten(philo) == TRUE)
	{
		printf("philo[i].has_eaten = %d\n",philo->has_eaten);
		printf("philo->root->number_of_times_each_philosopher_must_eat = %d\n", philo->number_of_times_each_philosopher_must_eat);
		printf("EVERYONE IS FED, congratulations\n"); // ne pas oublier de break ou free ici
		exit(0);
	}
	printf("IL a mange %d nombre de repas\n", philo->has_eaten);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_right_hand]);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_left_hand]);
	return (0);
}

void	*philo_is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->sleep[philo->id]);
	printf("philo %d is sleeping\n", philo->id);
	usleep(philo->root->time_to_sleep);
	pthread_mutex_unlock(&philo->root->sleep[philo->id]);
	return (0);
}

void	*philo_has_taken_a_fork(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);
	philo->root = (t_root *)malloc(sizeof(t_root));
	if (philo->id % 2 == 0)
		usleep(500000);
	//printf("philo->root->number_of_times_each_philosopher_must_eat = %d\n", philo->root->time_to_eat);
	while (1) // rajouter condition tant que philo non mort
	{
		// printf("philo->root->number_of_times_each_philosopher_must_eat = %d\n", philo->root->time_to_eat);
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		printf("philo %d is thinking\n", philo->id);
		usleep(1000000);
	}
	if (philo->root)
		free(philo->root);
	return (0);
}
