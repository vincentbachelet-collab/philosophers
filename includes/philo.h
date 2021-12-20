/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:03:40 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/20 15:47:19 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define FALSE 1
# define TRUE 0

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct philo
{
	int				fork_left_hand;
	int				fork_right_hand;
	int				id;
	int				has_eaten;
	int				last_meal;
	int				is_eating;
	struct s_root	*root;
	struct timeval	count;
	pthread_t		thread;
	pthread_t		philo_death;
}	t_philo;

typedef struct s_root {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;	
	int				id_dead_philo;	
	int				dead_philo;
	int				number_of_times_each_philosopher_must_eat;
	int				everyone_has_eaten;
	struct timeval	start;
	struct timeval	end;
	pthread_mutex_t	fork[255];
	pthread_mutex_t	sleep[255];
	pthread_mutex_t	death;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	has_eaten;
	pthread_mutex_t	all_meals_eaten;
	pthread_mutex_t	blabla;
	t_philo			philo[255];
}	t_root;

int				errors_start_handling(t_root *infos, char **argv);
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
void			ft_putendl_fd(char *s, int fd);
void			*routine(void *arg);
int				thread_philo_creation(t_root *infos);
int				init_infos_philo(t_root *infos, char **argv, int argc);
void			*philo_has_taken_a_fork(void *arg);
int				free_malloc_and_exit(t_root *infos, int i);
int				numbers_of_philosophers_is_pair(t_root *infos);
int				philo_eat_pair_impair(t_root *infos);
int				p_thread_create_join(t_root *infos);
void			init_count_has_eaten(t_root *infos);
int				check_if_number_of_has_been_eaten(t_root *infos, int i);
int				a_philo_is_dead(t_root *infos, int i);
void			*philo_is_sleeping(t_philo *philo);
int				get_current_time(t_philo *philo);
int				check_if_philo_is_dead(t_root *infos, int i);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				philo_is_eating(t_philo *philo);
int				check_if_everyone_has_eaten(t_philo *philo);
void			*philo_is_sleeping(t_philo *philo);
int				a_philo_has_eaten_his_meals(t_philo *philo);
int				a_philo_is_dead(t_root *infos, int i);
int				philo_is_dead_mutex(t_root *infos);
int				time_since_last_meal(t_root *infos, int i);
long long int	ft_atol(const char *str);

#endif
