/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_and_death_philo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/16 01:17:41 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_number_of_has_been_eaten(t_philo *philo)
{
	if ((philo->id == philo->root->number_of_philosophers)
		&& (philo->root->number_of_times_each_philosopher_must_eat 
		== philo->has_eaten))
	{
		philo->root->everyone_has_eaten = 1;
		printf("EVERYONE IS FED, congratulations\n");
		return (TRUE);
	}
	return (FALSE);
}

void*	check_if_philo_is_dead(void *arg)
{	
	t_philo	*philo;

	philo = ((t_philo *)arg);
	while (philo->root->everyone_has_eaten == 0 || philo->root->dead_philo == 0)
	{
		while (philo->root->dead_philo == 0)
		{	
			pthread_mutex_lock(&philo->root->death[philo->id]);
			if (get_current_time(philo) - philo->last_meal >= philo->root->time_to_die)
			{
				pthread_mutex_lock(&philo->root->print_death[philo->id]);
				printf("%d ms: PHILO %d IS DEAD\n ", get_current_time(philo), philo->id);
				philo->root->dead_philo = 1;
				// break ;
				pthread_mutex_unlock(&philo->root->print_death[philo->id]);
			}
			pthread_mutex_unlock(&philo->root->death[philo->id]);
			usleep(500);
		}
		if (philo->root->dead_philo == 1 )
			break ;
	}
	return (0);
}