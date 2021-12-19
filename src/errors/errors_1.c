/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:40 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/19 19:28:34 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	errors_start_handling(t_root *infos, char **argv)
{
	int	i;
	int	j;

	(void) infos;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (ft_isdigit(argv[i][j]) == 1)
			j++;
		if (argv[i][j] != 0)
		{
			printf ("Arguments are not integers\n");
			return (1);
		}
		i++;
	}
	return (0);
}
