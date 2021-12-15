/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_and_death_philo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/15 12:56:38 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_number_of_has_been_eaten(t_philo *philo)
{
	if ((philo->id == philo->root->number_of_philosophers)
		&& (philo->root->number_of_times_each_philosopher_must_eat 
		== philo->has_eaten))
	{
		printf("EVERYONE IS FED, congratulations\n");
		return (TRUE);
	}
	return (FALSE);
}

int	check_if_philo_is_dead(t_philo *philo)
{
	struct timeval	count;
	struct timeval	end;
	int				time_since_last_lunch = 0;
	int				current_time;
	
	pthread_mutex_lock(&philo->root->death[philo->id]);
	current_time = get_current_time(philo);
	gettimeofday(&count, 0);
	time_since_last_lunch = 0;
	while (time_since_last_lunch <= philo->root->time_to_die)
	{
		usleep(50);
		gettimeofday(&end, 0);
		time_since_last_lunch = (end.tv_sec * 1000 + end.tv_usec / 1000) \
		- ( count.tv_sec * 1000 +  count.tv_usec / 1000);
		if	(time_since_last_lunch == philo->root->time_to_die)
		{
			printf("%d ms: philo %d is DEAD\n", time_since_last_lunch, philo->id);
			return (TRUE);
		}
	}
	return (FALSE);
	pthread_mutex_unlock(&philo->root->death[philo->id]);
	return (FALSE);
}
