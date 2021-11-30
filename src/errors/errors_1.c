/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:40 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 14:59:33 by vbachele         ###   ########.fr       */
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
			exit (1);
		}
		i++;
	}
	return (0);
}