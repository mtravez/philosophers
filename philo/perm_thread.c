/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:51:53 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/22 13:33:37 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*This function determines whether or not the program should end
by checking if a philosopher has died or if all philosophers have
eaten at least dead->max_eat times*/
int	check_floor(t_dead_time *dead)
{
	pthread_mutex_lock(&dead->mutex_dead);
	pthread_mutex_lock(&dead->mutex_ate);
	if (dead->someone_dead || dead->finished_eating)
	{
		pthread_mutex_unlock(&dead->mutex_dead);
		pthread_mutex_unlock(&dead->mutex_ate);
		return (1);
	}
	pthread_mutex_unlock(&dead->mutex_dead);
	pthread_mutex_unlock(&dead->mutex_ate);
	return (0);
}

/*This is thread will perpetually be checking for anything that
would end the program in a detached way. */
void	*bring_death(void *phil_array)
{
	t_phil			**phils;
	t_dead_time		*dead;
	int				i;

	phils = (t_phil **)phil_array;
	dead = phils[0]->dead_time;
	while (!check_floor(dead))
	{
		i = 0;
		while (i < dead->nr_phil)
		{
			if (check_floor(dead) || check_hunger(phils[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

/*This function initiates a detached thread to check for
dead philosophers and for a termination of the threads.*/
int	death_bringer(t_table *table)
{
	pthread_t	bringer;

	if (pthread_create(&bringer, NULL, \
		&bring_death, table->phils) != 0)
		return (0);
	pthread_detach(bringer);
	return (1);
}
