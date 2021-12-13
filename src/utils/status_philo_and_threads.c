/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:52:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/10 21:12:24 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_has_taken_a_fork(void *arg)
{
	t_philo	*philo;
	// int	fork;
	
	philo = ((t_philo *)arg);
	philo->root = (t_root *)malloc(sizeof(t_root));
	pthread_mutex_lock(&philo->root->fork[philo->fork_left_hand]);
	pthread_mutex_lock(&philo->root->fork[philo->fork_right_hand]);
	printf("philo %d is eating\n", philo->id);
	printf("philo %d has taken the right fork number %d\n", philo->id, philo->fork_right_hand);
	printf("philo %d has taken the left fork number %d\n", philo->id, philo->fork_left_hand);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_right_hand]);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_left_hand]);
	if (philo->root)
		free(philo->root);
	return (0);
}
