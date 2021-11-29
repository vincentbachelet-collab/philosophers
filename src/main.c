/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:03:11 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/29 17:18:34 by vbachele         ###   ########.fr       */
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
	srand(time(NULL));
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