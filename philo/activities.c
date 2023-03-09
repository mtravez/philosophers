/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:37:45 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/09 14:53:12 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *phil)
{
	// phil->fork->in_use = 1;
	// phil->fork->next->in_use = 1;
	printf("%lu %i has taken a fork\n", get_mil_time(phil->start), \
	phil->phil_id);
	gettimeofday(&(phil->last_ate), NULL);
	printf("%lu %i is eating\n", get_mil_time(phil->start), phil->phil_id);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_eat)
		;
	// phil->fork->in_use = 0;
	// phil->fork->next->in_use = 0;
	// pthread_mutex_unlock(&(phil->fork->next->mutex));
	// pthread_mutex_unlock(&(phil->fork->mutex));
}

int	sleep_phil(t_phil *phil)
{
	printf("%lu %i is sleeping\n", get_mil_time(phil->start), phil->phil_id);
	gettimeofday(&(phil->last_ate), NULL);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_sleep)
	{
		if (get_mil_time(phil->last_ate) >= phil->dead_time->time_starve)
		{
			printf("%lu %i died\n", get_mil_time(phil->start), phil->phil_id);
			return (0);
		}
	}
	return (1);
}

void	check_hunger(t_phil *phil)
{
	if (get_mil_time(phil->last_ate) >= phil->dead_time->time_starve)
	{
		printf("%lu %i died\n", get_mil_time(phil->start), phil->phil_id);
		exit (1);
	}
}

int	phil_ate(t_phil *phil, int ate)
{
	if (phil->dead_time->max_eat > 0 && ate > 0)
	{
		pthread_mutex_lock(&phil->dead_time->mutex_ate);
			phil->dead_time->phil_ate_max++;
			if (phil->dead_time->nr_phil <= phil->dead_time->phil_ate_max)
			{
				pthread_mutex_unlock(&phil->dead_time->mutex_ate);
				return (1);
			}
		pthread_mutex_unlock(&phil->dead_time->mutex_ate);
	}
	return (0);
}
