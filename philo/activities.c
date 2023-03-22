/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:37:45 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/22 16:00:42 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*This function replicates a philosopher eating. It will lock the
mutex for the philosopher's fork and the mutex for the next fork
and wait for the amount of time it takes a philosopher to eat, 
then it will unlock the mutexes and assign the phil's action to
the sleep_phil function*/
void	eat(t_phil *phil)
{
	if (check_floor(phil->dead_time))
	{
		pthread_mutex_unlock(&phil->fork->mutex);
		return ;
	}
	print_mute("has taken a fork", phil);
	pthread_mutex_lock(&(phil->fork->next->mutex));
	if (check_floor(phil->dead_time))
	{
		pthread_mutex_unlock(&phil->fork->next->mutex);
		pthread_mutex_unlock(&phil->fork->mutex);
		return ;
	}
	print_mute("has taken a fork", phil);
	usleep(100);
	gettimeofday(&(phil->last_ate), NULL);
	print_mute("is eating", phil);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_eat)
		usleep(50);
	pthread_mutex_unlock(&phil->fork->next->mutex);
	pthread_mutex_unlock(&phil->fork->mutex);
	phil->action = sleep_phil;
}

/*This function replictes the sleeping behavior in a philosopher.
It will wait for the amount of time it takes for a philosopher to sleep
and it will also be checking if the philosopher died. It then will
set the phil's action to think*/
void	sleep_phil(t_phil *phil)
{
	struct timeval	sleepy_time;

	print_mute("is sleeping", phil);
	gettimeofday(&sleepy_time, NULL);
	while (get_mil_time(sleepy_time) < phil->dead_time->time_sleep)
		usleep(50);
	phil->action = think;
}

/*This function replicates the thinking behavior. It will lock the
philosopher's fork's mutex and thus, will only continue to execute if
the fork is not being used by another thread. Then, it will set the
philosopher's action back to eat*/
void	think(t_phil *phil)
{
	print_mute("is thinking", phil);
	pthread_mutex_lock(&phil->fork->mutex);
	phil->action = &eat;
}

/*This function checks if there has been longer than the starving time
and sets the someone_dead variable to 1 if that is the case*/
int	check_hunger(t_phil *phil)
{
	pthread_mutex_lock(&phil->dead_time->mutex_dead);
	if (get_mil_time(phil->last_ate) >= phil->dead_time->time_starve)
	{
		print_mute("died", phil);
		pthread_mutex_unlock(&phil->fork->mutex);
		phil->dead_time->someone_dead = 1;
		pthread_mutex_unlock(&phil->dead_time->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&phil->dead_time->mutex_dead);
	return (0);
}

/*This function is called whenever a philosopher has eaten the minimum
required times and adds one to the number of philosophers who have
already eaten this many times. When all the philosophers have eaten the
required amount, the variable finished eating is changed to 1.*/
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
