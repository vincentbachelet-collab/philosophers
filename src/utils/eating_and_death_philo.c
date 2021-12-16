/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_and_death_philo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/16 19:01:06 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

fun check_someone_died
int i;

pthread_lock(truc)
i = truc_que_tu_veux_lire
pthread_unlock(truc)
return i

if (.... && check_if_someone_died(nbr philo) ==0)

#include "philo.h"

int	check_if_number_of_has_been_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->death[philo->id]);
	pthread_mutex_lock(&philo->root->check_death[philo->id]);
	if ((philo->id == philo->root->number_of_philosophers)
		&& (philo->root->number_of_times_each_philosopher_must_eat 
		== philo->has_eaten) && philo->root->dead_philo == 0 && )
	{
		philo->root->everyone_has_eaten = 1;
		printf("EVERYONE IS FED, congratulations\n");
		pthread_mutex_unlock(&philo->root->death[philo->id]);
		pthread_mutex_unlock(&philo->root->check_death[philo->id]);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->root->check_death[philo->id]);
	pthread_mutex_unlock(&philo->root->death[philo->id]);
	return (FALSE);
}

void*	check_if_philo_is_dead(void *arg)
{	
	t_philo	*philo;

	philo = ((t_philo *)arg);
	while (philo->root->dead_philo == 0 && philo->root->everyone_has_eaten == 0)
	{	
		// pthread_mutex_lock(&philo->root->death[philo->id]);
		check_if_number_of_has_been_eaten(philo);
		pthread_mutex_lock(&philo->root->death[philo->id]);
		if (get_current_time(philo) - philo->last_meal >= philo->root->time_to_die 
			&& philo->is_eating == 0 && philo->root->dead_philo == 0
			&& philo->root->everyone_has_eaten == 0)
		{
			pthread_mutex_lock(&philo->root->print_death[philo->id]);
			printf("%d ms philo %d IS DEAD\n", get_current_time(philo), philo->id);
				philo->root->dead_philo = 1;
			usleep(500);
			pthread_mutex_unlock(&philo->root->print_death[philo->id]);
		}
		pthread_mutex_unlock(&philo->root->death[philo->id]);
		usleep(500);
	}
	return (0);
}