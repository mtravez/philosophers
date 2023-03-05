/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:03:25 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/05 14:12:20 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_mil_time(struct timeval start)
{
	struct timeval stop;
	gettimeofday(&stop, NULL);
	return ((stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000);
}

void	phil_ate(t_phil *phil, int ate)
{
	if (phil->dead_time->max_eat > 0)
	{
		if (ate == phil->dead_time->max_eat)
		{
			phil->dead_time->phil_ate_max++;
			if (phil->dead_time->max_eat == phil->dead_time->phil_ate_max)
				exit (0);
		}
	}
}
