/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:03:11 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/10 17:25:14 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;

void	*routine()
{
	int value;
	int *res;
	
	res = NULL;
	pthread_mutex_lock(&mutex);
	value = (rand() % 6) + 1;
	res = malloc(sizeof(int));
	*res = value;
	pthread_mutex_unlock(&mutex);
	return (void *) res;
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	// struct timeval start;
	// struct timeval end;
	int			i;
	int 		*res;
	pthread_t	th[8];
	
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 8)
	{
		if (pthread_create(th + i, NULL, &routine, NULL)  != 0)
		{
			printf ("Error\n");
			return (i);
		}
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], (void **) &res) != 0)
		{
		printf ("Error\n");
		return (i);
		}
		printf ("le resultat du jet de des est %d\n", *res);
		free (res);
		i++;	
	}
	pthread_mutex_destroy(&mutex);
	// gettimeofday(&start, 0);
	
	// printf("prout\n");
	// gettimeofday(&end, 0);
	// printf("ca a pris %ld ms", (end.tv_usec - start.tv_usec));
	return (0);
}


typedef	struct philo
{
	int				fork_left_hand;
	int				fork_right_hand;
	pthread_t 		thread[255]; // le philo dans le thread
	struct	s_root	*root;
} t_philo;


typedef struct s_root {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_t		th[255];
	pthread_mutex_t	*fork; // les fourchettes immobillises qu'on va calculer grace a un ID
	t_philo			*philo;
}
t_root;