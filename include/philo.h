/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:03:40 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/10 20:15:41 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

typedef	struct philo
{
	int				fork_left_hand;
	int				fork_right_hand;
	int				id;
	struct s_root	*root;
	pthread_t 		thread;
} t_philo;


typedef struct s_root {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	fork[255];
	t_philo			philo[255];
}
t_root;

int		errors_start_handling(t_root *infos, char **argv);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	ft_putendl_fd(char *s, int fd);
void	*routine(void *arg);
int		thread_philo_creation(t_root *infos);
int		init_infos_philo(t_root *infos, char **argv);
void	*philo_has_taken_a_fork(void *arg);
int		free_malloc_and_exit(t_root *infos, int i);

#endif