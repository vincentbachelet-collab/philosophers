/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:55:25 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/14 17:57:16 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_root			infos[1];

	memset(&infos, 0, sizeof infos);
	if (argc == 6 || argc == 5)
	{
		errors_start_handling(infos, argv);
		init_infos_philo(infos, argv);
		thread_philo_creation(infos);
	}
	else
		ft_putendl_fd("Wrong number of arguments, it sould be 4.\n"
			"1.number_of_philosophers| 2.time_to_die |3.time_to_eat"
			"|4.time_to_sleep"
			"| 5.[number_of_times_each_philosopher_must_eat]\n", 2);
	free_malloc_and_exit(infos, 0);
	return (0);
}
