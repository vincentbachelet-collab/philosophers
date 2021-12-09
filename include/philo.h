/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:03:40 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/09 16:03:25 by vbachele         ###   ########.fr       */
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

typedef struct s_root {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}
t_root;

int		errors_start_handling(t_root *infos, char **argv);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	ft_putendl_fd(char *s, int fd);
void	*routine(void *arg);
int		thread_philo_creation(t_root *infos);
int		init_infos_philo(t_root *infos, char **argv);

#endif