/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2nd_thread_eating_and_death_philo.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/20 12:02:51 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_since_last_meal(t_root *infos, int i)
{
	int j;
	
	pthread_mutex_lock(&infos->last_meal);
	j = get_current_time(&infos->philo[i]) - infos->philo[i].last_meal;
	// printf("timne since last meal == %d -- philo n: %d\n", j, i);
	pthread_mutex_unlock(&infos->last_meal);
	return (j);
}

int philo_is_dead_mutex(t_root *infos)
{
	int j;
	infos->dead_philo = 1;
	j = infos->dead_philo;
	return (j);
	
}

int	a_philo_is_dead(t_root *infos, int i)
{
	pthread_mutex_lock(&infos->death);
	// pthread_mutex_lock(&infos->all_meals_eaten);
	pthread_mutex_lock(&infos->is_eating);
	if (time_since_last_meal(infos, i) >= infos->time_to_die 
		&& infos->philo[i].is_eating == 0 && infos->dead_philo == 0
		&& infos->everyone_has_eaten == 0)
	{
		pthread_mutex_unlock(&infos->is_eating);
		philo_is_dead_mutex(infos);
		pthread_mutex_unlock(&infos->death);
		pthread_mutex_lock(&infos->blabla);
		ft_putnbr_fd(get_current_time(&infos->philo[i]), 1);
		ft_putstr_fd(" ms philo ", 1);
		ft_putnbr_fd(infos->philo[i].id, 1);
		ft_putstr_fd(" IS DEAD\n", 1);
		pthread_mutex_unlock(&infos->blabla);
		// pthread_mutex_unlock(&infos->death);
		// pthread_mutex_unlock(&infos->all_meals_eaten);
		return (1);
	}
	pthread_mutex_unlock(&infos->is_eating);
	pthread_mutex_unlock(&infos->death);
	// pthread_mutex_unlock(&infos->all_meals_eaten);
	return (0);
}

int check_how_many_meals_philo_has_eaten(t_root *infos, int i)
{
	int	j;
	
	pthread_mutex_lock(&infos->has_eaten);
	j = infos->philo[i].has_eaten;
	pthread_mutex_unlock(&infos->has_eaten);
	return (j);
}


int	check_if_number_of_has_been_eaten(t_root *infos, int i)
{
	
	if ((i == infos->number_of_philosophers)
		&& (infos->number_of_times_each_philosopher_must_eat
			== check_how_many_meals_philo_has_eaten(infos, i))
		&& infos->dead_philo == 0)
	{
		pthread_mutex_lock(&infos->all_meals_eaten);
		pthread_mutex_lock(&infos->blabla);
		infos->everyone_has_eaten = 1;
		ft_putendl_fd("EVERYONE IS FED, congratulations", 1);
		pthread_mutex_unlock(&infos->blabla);
		pthread_mutex_unlock(&infos->all_meals_eaten);
		return (1);
	}
	return (0);
}

int		check_if_philo_is_dead(t_root *infos, int i)
{	
	if (a_philo_is_dead(infos, i) == 1)
		return (1);
	if (check_if_number_of_has_been_eaten(infos, i) == 1)
		return (1);
	return (0);
}