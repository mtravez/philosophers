/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:37:45 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/13 17:09:54 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *phil)
{
	print_mute("has taken a fork", phil);
	if (phil->dead_time->nr_phil != 1)
	{
		pthread_mutex_lock(&(phil->fork->next->mutex));
		print_mute("has taken a fork", phil);
	}
	gettimeofday(&(phil->last_ate), NULL);
	print_mute("is eating", phil);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_eat)
		usleep(100);
	if (phil->dead_time->nr_phil != 1)
		pthread_mutex_unlock(&phil->fork->next->mutex);
	pthread_mutex_unlock(&phil->fork->mutex);
}

void	sleep_phil(t_phil *phil)
{
	print_mute("is sleeping", phil);
	gettimeofday(&(phil->last_ate), NULL);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_sleep)
	{
		if (get_mil_time(phil->last_ate) >= phil->dead_time->time_starve)
		{
			printf("%lu %i died\n", get_mil_time(phil->start), phil->phil_id);
			return ;
		}
		usleep(100);
	}
}

void	think(t_phil *phil)
{
	print_mute("is thinking", phil);
	pthread_mutex_lock(&phil->fork->mutex);
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
