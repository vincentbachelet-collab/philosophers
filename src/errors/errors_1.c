/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:40 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/10 17:37:23 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	errors_start_handling(t_root *infos, char **argv)
{
	(void) infos;
	int	i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (ft_isdigit(argv[i][j]) == 1)
			j++;
		if (argv[i][j] != 0)
		{
			printf ("Arguments are not integers\n");
			free_malloc_and_exit(infos, 1);
		}
		i++;
	}
	return (0);
}

int	init_infos_philo(t_root *infos, char **argv)
{
	if ((infos->number_of_philosophers = ft_atoi(argv[1])) < 1)
		ft_putendl_fd("philophers can't be less than one", 2);
	if ((infos->number_of_philosophers = ft_atoi(argv[1])) >= 200)
		ft_putendl_fd("philophers can't be more than 200", 2);
	if ((infos->time_to_die = ft_atoi(argv[2])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	if ((infos->time_to_eat = ft_atoi(argv[3])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	if ((infos->time_to_eat = ft_atoi(argv[4])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	if ((infos->number_of_times_each_philosopher_must_eat = atoi(argv[5])) < 0)
		ft_putendl_fd("args can't be negative", 2);
	return (0);
}