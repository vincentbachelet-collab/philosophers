/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_and_death_philo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/15 18:22:55 by vbachele         ###   ########.fr       */
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

int	check_if_philo_is_dead(t_root *infos)
{	
	// int i;

	// i = 0;
	(void) infos;
	pthread_mutex_lock(&infos->death[infos->philo->id]);
	printf("infos->philo[infos->philo->id].last_meal == %d", infos->philo[infos->philo->id].last_meal);
	if (infos->philo[infos->philo->id].last_meal - get_current_time(infos->philo) >= infos->time_to_die)
	{
		// usleep(50);
		// printf("%d ms: philo %d is DEAD\n", get_current_time(infos->philo), infos->philo->id);
		// infos->philo->id = philo->root->id_dead_philo;
		infos->dead_philo = 1;
	}
		pthread_mutex_unlock(&infos->death[infos->philo->id]);
	return (FALSE);
}