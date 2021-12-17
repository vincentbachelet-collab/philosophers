/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:52:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/17 15:56:33 by vbachele         ###   ########.fr       */
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

void	philo_is_eating_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->is_eating[philo->id]);
	pthread_mutex_lock(&philo->root->has_eaten[philo->id]);
	philo->is_eating = 1; // mettre un lock 
	philo->has_eaten++;
	usleep(philo->root->time_to_eat);
	philo->is_eating = 0;
	// philo->last_meal = get_current_time(philo);
	pthread_mutex_unlock(&philo->root->has_eaten[philo->id]);
	pthread_mutex_unlock(&philo->root->is_eating[philo->id]);
}
int	philo_is_eating(t_philo *philo)
{
	
	int current_time;
	pthread_mutex_lock(&philo->root->fork[philo->fork_left_hand]);
	pthread_mutex_lock(&philo->root->fork[philo->fork_right_hand]);
	pthread_mutex_lock(&philo->root->death[philo->id]);
	current_time = get_current_time(philo);
	if (philo->root->dead_philo == 0)
	{
		printf("%d ms philo %d has taken a fork %d\n",
			current_time, philo->id, philo->fork_right_hand);
		printf("%d ms philo %d has taken a fork %d\n",
			current_time, philo->id, philo->fork_left_hand);
		printf("%d ms philo %d is eating\n", current_time, philo->id);
		philo_is_eating_mutex(philo);
	}
	philo->last_meal = get_current_time(philo);
	pthread_mutex_unlock(&philo->root->death[philo->id]);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_right_hand]);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_left_hand]);
	return (0);
}

int	check_if_everyone_has_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->has_eaten[philo->id]);
	if (philo->root->everyone_has_eaten == 1)
	{
		pthread_mutex_unlock(&philo->root->has_eaten[philo->id]);	
		return (1);
	}
	pthread_mutex_unlock(&philo->root->has_eaten[philo->id]);
	return (0);
}

void	*philo_is_sleeping(t_philo *philo)
{
	int current_time;

	pthread_mutex_lock(&philo->root->sleep[philo->id]);
	current_time = get_current_time(philo);
	if (philo->root->dead_philo == 0)
	{
		printf("%d ms philo %d is sleeping\n", current_time, philo->id);
		usleep(philo->root->time_to_sleep);
	}
	pthread_mutex_unlock(&philo->root->sleep[philo->id]);
	return (0);
}

int a_philo_has_eaten_his_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->has_eaten[philo->id]);
	if (philo->has_eaten == philo->root->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(&philo->root->death[philo->id]);
		return (1);
	}
	pthread_mutex_unlock(&philo->root->has_eaten[philo->id]);
	return (0);
}

void	*philo_has_taken_a_fork(void *arg)
{
	t_philo	*philo;
	int		current_time;

	philo = ((t_philo *)arg);
	if (philo->id % 2 == 0)
			usleep(50000);
	pthread_mutex_lock(&philo->root->death[philo->id]);
	while(philo->root->dead_philo == 0)
	{
		philo_is_eating(philo);
		if (check_if_everyone_has_eaten(philo) == 1)
		{
			pthread_mutex_unlock(&philo->root->death[philo->id]);
			return (0);
		}
		philo_is_sleeping(philo);
		current_time = get_current_time(philo);
		if (philo->root->dead_philo == 0)
			printf("%d ms philo %d is thinking\n", current_time, philo->id);
		pthread_mutex_unlock(&philo->root->death[philo->id]);
		if (a_philo_has_eaten_his_meals(philo) == 1)
		{
			pthread_mutex_unlock(&philo->root->death[philo->id]);
			return (0);
		}
		pthread_mutex_unlock(&philo->root->death[philo->id]);
	}
	return (0);
}
