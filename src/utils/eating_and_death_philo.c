/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_and_death_philo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/14 18:59:11 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_number_of_has_been_eaten(t_philo *philo)
{
	// int	i;
	int j;

	// i = 0;
	j = 0;
	if (philo->root->number_of_philosophers % 2 == 0)
		j = philo->root->number_of_philosophers;
	else
		j = philo->root->number_of_philosophers - 1;
	if (philo->id == j) // a ne pas init ici
	{
		if (philo->has_eaten == philo->root->number_of_times_each_philosopher_must_eat)
			return (TRUE); 	
		else
			return (FALSE);
	}
	return (FALSE);
}

int	check_if_philo_is_dead(t_philo *philo)
{
	struct timeval	count;
	int	time_since_last_lunch;
	int current_time;
	
	pthread_mutex_lock(&philo->root->death[philo->id]);
	current_time = get_current_time(philo);
	gettimeofday(&count, 0);
	while (time_since_last_lunch <= philo->root->time_to_die)
	{
		// printf("\ntime_since_last_lunch == %d/n", time_since_last_lunch);
		gettimeofday(&philo->root->end, 0);
		time_since_last_lunch = (philo->root->end.tv_sec * 1000
		+ philo->root->end.tv_usec / 1000) \
		- ( count.tv_sec * 1000 +  count.tv_usec / 1000);
		if	(time_since_last_lunch == philo->root->time_to_die)
		{
			printf("%d ms: philo %d is DEAD\n", current_time, philo->id);
			return (TRUE);
		}
		gettimeofday(&philo->root->end, 0);
	}
	pthread_mutex_unlock(&philo->root->death[philo->id]);
	return (FALSE);
}
