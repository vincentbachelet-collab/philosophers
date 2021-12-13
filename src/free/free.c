/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:33:12 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/10 18:18:26 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_malloc_and_exit(t_root *infos, int i)
{
	(void) infos;
	// if (infos->philo)
	// 	free(infos->philo);
	// if (infos->fork)
	// 	free(infos->fork);
	if (i == 0)
		exit (0);
	else 
		exit (1);
}

