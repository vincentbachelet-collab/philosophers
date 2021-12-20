/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:32:54 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/20 14:35:23 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead_mutex(t_root *infos)
{
	int	j;

	infos->dead_philo = 1;
	j = infos->dead_philo;
	return (j);
}

int	a_philo_is_dead(t_root *infos, int i)
{
	pthread_mutex_lock(&infos->death);
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
		return (1);
	}
	pthread_mutex_unlock(&infos->is_eating);
	pthread_mutex_unlock(&infos->death);
	return (0);
}
