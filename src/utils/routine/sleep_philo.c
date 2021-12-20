/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:24:03 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/20 14:24:13 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_is_sleeping(t_philo *philo, int current_time)
{
	pthread_mutex_lock(&philo->root->blabla);
	ft_putnbr_fd(current_time, 1);
	ft_putstr_fd(" ms philo ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is sleeping\n", 1);
	pthread_mutex_unlock(&philo->root->blabla);
}

void	*philo_is_sleeping(t_philo *philo)
{
	int	current_time;

	pthread_mutex_lock(&philo->root->sleep[philo->id]);
	pthread_mutex_lock(&philo->root->death);
	current_time = get_current_time(philo);
	if (philo->root->dead_philo == 0)
		print_philo_is_sleeping(philo, current_time);
	pthread_mutex_unlock(&philo->root->death);
	pthread_mutex_unlock(&philo->root->sleep[philo->id]);
	return (0);
}
