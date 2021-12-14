/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_and_death_philo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/14 15:44:34 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat_pair_impair(t_root *infos)
{
	int i;
	
	i = 1;
	while (i <= infos->number_of_philosophers) // je pthreadcreate et gere chacun de mes philo
	{
		if (pthread_create(&infos->philo[i].thread, NULL,
			&philo_has_taken_a_fork, &infos->philo[i]) != 0)
		{
			ft_putendl_fd("Error_pthread_create_init\n", 2);
			return (1);
		}
		i ++;
		// pendant ce TEMPS LA LESAUTRE DORMENTS OU PENSENT LE TEMPS DU USLEEP
	}
	return (0);
}


int	check_if_number_of_has_been_eaten(t_philo *philo)
{
	// int	i;
	int j;

	// i = 0;
	j = 0;
	if (philo->number_of_philosophers % 2 == 0)
		j = philo->number_of_philosophers;
	else
		j = philo->number_of_philosophers - 1;
	if (philo->id == j) // a ne pas init ici
	{
		if (philo->has_eaten == philo->number_of_times_each_philosopher_must_eat)
			return (TRUE); 	
		else
			return (FALSE);
	}
	return (FALSE);
}

int	check_if_philo_is_dead(t_philo *philo)
{
	// struct timeval	start;
	
	gettimeofday(&philo->start, 0);
	// while (philo->start < philo->time_to_die)
	// {
		
	// }
	return (0);
}
