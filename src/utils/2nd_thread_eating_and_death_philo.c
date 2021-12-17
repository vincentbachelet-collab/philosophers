/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2nd_thread_eating_and_death_philo.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/17 16:40:35 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	a_philo_is_dead(t_root *infos, int i)
{
	pthread_mutex_lock(&infos->has_eaten[infos->philo[i].id]);
	if (get_current_time(&infos->philo[i]) - infos->philo[i].last_meal >= infos->time_to_die 
		&& infos->philo[i].is_eating == 0 && infos->dead_philo == 0
		&& infos->everyone_has_eaten == 0)
	{
		printf("%d ms philo %d IS DEAD\n", get_current_time(&infos->philo[i]), infos->philo[i].id);
			infos->dead_philo = 1;
		usleep(500);
		pthread_mutex_unlock(&infos->has_eaten[infos->philo[i].id]);
		return (1);
	}
	pthread_mutex_unlock(&infos->has_eaten[infos->philo[i].id]);

	usleep(500);
	return (0);
}

int	check_if_number_of_has_been_eaten(t_root *infos, int i)
{
	pthread_mutex_lock(&infos->death[i]);
	pthread_mutex_lock(&infos->has_eaten[i]);
	// printf ("\ni                   == %d\n"
	// 		"infos->number_of_philosophers == %d\n"
	// 		"infos->philo[i].has_eaten     == %d\n"
	// 		"infos->dead_philo             == %d\n", i, infos->number_of_philosophers, 
	// 		infos->philo[i].has_eaten, infos->dead_philo);
	if ((i == infos->number_of_philosophers)
		&& (infos->number_of_times_each_philosopher_must_eat 
			== infos->philo[i].has_eaten) 
		&& infos->dead_philo == 0)
	{
		infos->everyone_has_eaten = 1;
		printf("EVERYONE IS FED, congratulations\n");
		pthread_mutex_unlock(&infos->death[i]);
		pthread_mutex_unlock(&infos->has_eaten[i]);
		return (TRUE);
	}
	pthread_mutex_unlock(&infos->has_eaten[i]);
	pthread_mutex_unlock(&infos->death[i]);
	return (FALSE);
}

int		check_if_philo_is_dead(t_root *infos, int i)
{	
	pthread_mutex_lock(&infos->has_eaten[i]);
	pthread_mutex_lock(&infos->death[i]);
	check_if_number_of_has_been_eaten(infos, i);
	if (a_philo_is_dead(infos, i) == 1)
	{
		pthread_mutex_unlock(&infos->death[i]);
		pthread_mutex_unlock(&infos->has_eaten[i]);
		return (1);
	}
	pthread_mutex_unlock(&infos->death[i]);
	pthread_mutex_unlock(&infos->has_eaten[i]);
	return (0);
}