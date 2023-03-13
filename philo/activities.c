/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:37:45 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/13 20:16:32 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *phil)
{
	if (check_hunger(phil))
		return ;
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
	phil->action = sleep_phil;
}

void	sleep_phil(t_phil *phil)
{
	print_mute("is sleeping", phil);
	gettimeofday(&(phil->last_ate), NULL);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_sleep)
	{
		if (check_hunger(phil))
			return ;
		usleep(100);
	}
	phil->action = think;
}

void	think(t_phil *phil)
{
	print_mute("is thinking", phil);
	pthread_mutex_lock(&phil->fork->mutex);
	phil->action = &eat;
}

int	check_hunger(t_phil *phil)
{
	if (get_mil_time(phil->last_ate) >= phil->dead_time->time_starve)
	{
		print_mute("died", phil);
		pthread_mutex_lock(&phil->dead_time->mutex_dead);
		phil->dead_time->someone_dead = 1;
		pthread_mutex_unlock(&phil->dead_time->mutex_dead);
		return (1);
	}
	return (0);
}

void	phil_ate(t_phil *phil, int ate)
{
	if (phil->dead_time->max_eat > 0 && ate > 0)
	{
		pthread_mutex_lock(&phil->dead_time->mutex_ate);
		phil->dead_time->phil_ate_max++;
		if (phil->dead_time->nr_phil <= phil->dead_time->phil_ate_max)
		{
			phil->dead_time->finished_eating = 1;
			pthread_mutex_unlock(&phil->dead_time->mutex_ate);
		}
		pthread_mutex_unlock(&phil->dead_time->mutex_ate);
	}
}
