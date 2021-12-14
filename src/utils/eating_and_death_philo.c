/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_and_death_philo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:42 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/14 17:18:33 by vbachele         ###   ########.fr       */
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

// int	check_if_philo_is_dead(t_philo *philo)
// {
// 	// struct timeval	start;
	
// 	gettimeofday(&philo->root->start, 0);
// 	// while (philo->start < philo->time_to_die)
// 	// {
		
// 	// }
// 	return (0);
// }
