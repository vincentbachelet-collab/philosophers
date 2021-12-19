/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:52:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/19 20:43:50 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_current_time(t_philo *philo)
{
	int current_time;
	
	gettimeofday(&philo->root->end, 0);
	current_time = (philo->root->end.tv_sec * 1000
		+ philo->root->end.tv_usec / 1000) \
		- (philo->root->start.tv_sec * 1000 + philo->root->start.tv_usec / 1000);
	return (current_time);
}

void	print_philo_is_thinking(t_philo *philo, int current_time)
{
	pthread_mutex_lock(&philo->root->blabla);
	ft_putnbr_fd(current_time, 1);
	ft_putstr_fd(" ms philo ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->root->blabla);

}

void	*philo_has_taken_a_fork(void *arg)
{
	t_philo	*philo;
	int		current_time;

	philo = ((t_philo *)arg);
	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		pthread_mutex_lock(&philo->root->death);
		if (philo->root->dead_philo == 1)
		{
			pthread_mutex_unlock(&philo->root->death);
			return (0);
		}
		pthread_mutex_unlock(&philo->root->death);
		philo_is_eating(philo);
		if (check_if_everyone_has_eaten(philo) == 1)
			return (0);
		philo_is_sleeping(philo);
		usleep(philo->root->time_to_sleep);
		current_time = get_current_time(philo);
		pthread_mutex_lock(&philo->root->death);
		if (philo->root->dead_philo == 0)
			print_philo_is_thinking(philo, current_time);
		pthread_mutex_unlock(&philo->root->death);
		if (a_philo_has_eaten_his_meals(philo) == 1)
			return (0);
	}
	return (0);
}
